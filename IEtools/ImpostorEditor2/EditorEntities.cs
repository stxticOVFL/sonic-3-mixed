using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace ImpostorEditor2
{
    class EditorEntities : IDrawable
    {
        List<EditorEntity> entities = new List<EditorEntity>();
        List<EditorEntity> selectedEntities = new List<EditorEntity>();
        List<EditorEntity> tempSelection = new List<EditorEntity>();

        Dictionary<byte, EditorEntity> entitiesBySlot = new Dictionary<byte, EditorEntity>();

        byte nextFreeSlot = 0;

        public List<EditorEntity> Entities { get { return entities; } }
        public List<EditorEntity> SelectedEntities { get { return selectedEntities; } }

        public class TooManyEntitiesException : Exception { }

        public Actions.IAction LastAction;


        public EditorEntities(RSDKv5.Scene scene)
        {
            foreach (var obj in scene.ObjectDefinitions)
                entities.AddRange(obj.ObjectList.Select(x => new EditorEntity(x)));
            entitiesBySlot = entities.ToDictionary(x => x.Entity.Unused);
        }

        private ushort getFreeSlot(RSDKv5.Scene.ISCN_Object preferred)
        {
            if (preferred != null && !entitiesBySlot.ContainsKey(preferred.Unused)) return preferred.Unused;
            while (entitiesBySlot.ContainsKey(nextFreeSlot))
            {
                ++nextFreeSlot;
            }
            if (nextFreeSlot == 2048)
            {
                if (entitiesBySlot.Count < 2048)
                {
                    // Next time search from beggining
                    nextFreeSlot = 0;
                }
                throw new TooManyEntitiesException();
            }
            return nextFreeSlot++;
        }

        public void Select(Rectangle area, bool addSelection = false, bool deselectIfSelected = false)
        {
            if (!addSelection) Deselect();
            foreach (var entity in entities)
            {
                if (entity.IsInArea(area))
                {
                    if (deselectIfSelected && selectedEntities.Contains(entity))
                    {
                        selectedEntities.Remove(entity);
                        entity.Selected = false;
                    }
                    else if (!selectedEntities.Contains(entity))
                    {
                        selectedEntities.Add(entity);
                        entity.Selected = true;
                    }
                }
            }
        }

        public void Select(Point point, bool addSelection = false, bool deselectIfSelected = false)
        {
            if (!addSelection) Deselect();
            // In reverse because we want to select the top one
            foreach (EditorEntity entity in entities.Reverse<EditorEntity>())
            {
                if (entity.ContainsPoint(point))
                {
                    if (deselectIfSelected && selectedEntities.Contains(entity))
                    {
                        selectedEntities.Remove(entity);
                        entity.Selected = false;
                    }
                    else
                    {
                        selectedEntities.Add(entity);
                        entity.Selected = true;
                    }
                    // Only the top
                    break;
                }
            }
        }

        public void SelectSlot(int slot)
        {
            Deselect();
            if (entitiesBySlot.ContainsKey((byte)slot))
            {
                selectedEntities.Add(entitiesBySlot[(byte)slot]);
                entitiesBySlot[(byte)slot].Selected = true;
            }
        }

        private void AddEntities(List<EditorEntity> entities)
        {
            foreach (var entity in entities)
            {
                entity.Entity.Definition.ObjectList.Add(entity.Entity);
                this.entities.Add(entity);
                entitiesBySlot[entity.Entity.Unused] = entity;
            }
        }

        private void DeleteEntities(List<EditorEntity> entities)
        {
            foreach (var entity in entities)
            {
                entity.Entity.Definition.ObjectList.Remove(entity.Entity);
                this.entities.Remove(entity);
                entitiesBySlot.Remove(entity.Entity.Unused);
                if (entity.Entity.Unused < nextFreeSlot) nextFreeSlot = entity.Entity.Unused;
            }
        }

        private void DuplicateEntities(List<EditorEntity> entities)
        {
            var new_entities = entities.Select(x => new EditorEntity(x.Entity.Copy())).ToList();
            if (new_entities.Count > 0)
                LastAction = new Actions.ActionAddDeleteEntities(new_entities.ToList(), true, x => AddEntities(x), x => DeleteEntities(x));
            AddEntities(new_entities);
            Deselect();
            selectedEntities.AddRange(new_entities);
            foreach (var entity in new_entities)
                entity.Selected = true;
        }

        public void MoveSelected(Point oldPos, Point newPos, bool duplicate)
        {
            Point diff = new Point(newPos.X - oldPos.X, newPos.Y - oldPos.Y);
            if (duplicate) DuplicateEntities(selectedEntities);
            foreach (var entity in selectedEntities)
            {
                entity.Move(diff);
            }
        }

        public bool IsSelected()
        {
            return selectedEntities.Count > 0 || tempSelection.Count > 0;
        }

        public void DeleteSelected()
        {
            if (selectedEntities.Count > 0)
                LastAction = new Actions.ActionAddDeleteEntities(selectedEntities.ToList(), false, x => AddEntities(x), x => DeleteEntities(x));
            DeleteEntities(selectedEntities);
            Deselect();
        }

        public List<EditorEntity> CopyToClipboard(bool keepPosition = false)
        {
            if (selectedEntities.Count == 0) return null;
            short minX = 0, minY = 0;

            List<EditorEntity> copiedEntities = selectedEntities.Select(x => new EditorEntity(x.Entity.Copy())).ToList();
            if (!keepPosition)
            {
                minX = copiedEntities.Min(x => x.Entity.X);
                minY = copiedEntities.Min(x => x.Entity.Y);
                copiedEntities.ForEach(x => x.Move(new Point(-minX, -minY)));
            }

            return copiedEntities;
        }

        public void PasteFromClipboard(Point newPos, List<EditorEntity> entities)
        {
            DuplicateEntities(entities);
            foreach (var entity in selectedEntities)
            {
                // Move them
                entity.Move(newPos);
            }
        }

        public EditorEntity GetEntityAt(Point point)
        {
            foreach (EditorEntity entity in entities.Reverse<EditorEntity>())
                if (entity.ContainsPoint(point))
                    return entity;
            return null;
        }

        public void TempSelection(Rectangle area, bool deselectIfSelected)
        {
            List<EditorEntity> newSelection = (from entity in entities where entity.IsInArea(area) select entity).ToList();

            foreach (var entity in (from entity in tempSelection where !newSelection.Contains(entity) select entity))
            {
                entity.Selected = selectedEntities.Contains(entity);
            }

            tempSelection = newSelection;

            foreach (var entity in newSelection)
            {
                entity.Selected = !deselectIfSelected || !selectedEntities.Contains(entity);
            }
        }
        public void Deselect()
        {
            foreach (var entity in entities)
            {
                entity.Selected = false;
            }
            selectedEntities.Clear();
        }

        public void EndTempSelection()
        {
            tempSelection.Clear();
        }

        public void Draw(Graphics g)
        {

        }

        public void Draw(DevicePanel d)
        {
            foreach (var entity in entities)
                entity.Draw(d);
        }

    }
}
