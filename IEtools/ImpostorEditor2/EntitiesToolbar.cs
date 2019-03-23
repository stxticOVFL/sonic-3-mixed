using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImpostorEditor2
{
    public partial class EntitiesToolbar : UserControl
    {
        public Action<int> SelectedEntity;
        public Action<Actions.IAction> AddAction;

        private List<RSDKv5.Scene.ISCN_Object> entities;

        private RSDKv5.Scene.ISCN_Object currentEntity;

        public List<RSDKv5.Scene.ISCN_Object> Entities {
            set
            {
                entities = value.ToList();
                entities.Sort((x, y) => x.Unused.CompareTo(y.Unused));
                UpdateEntitiesList();
            }
        }

        bool updateSelected = true;

        public List<RSDKv5.Scene.ISCN_Object> SelectedEntities
        {
            set
            {
                UpdateEntitiesProperties(value);
            }
        }

        public bool NeedRefresh;

        /*private RSDKv5.SceneObject currentObject;*/

        public EntitiesToolbar()
        {
            InitializeComponent();
        }

        private void UpdateEntitiesList()
        {
            entitiesList.Items.Clear();
            entitiesList.ResetText();
            if (currentEntity != null && entities.Contains(currentEntity))
            {
                entitiesList.SelectedText = String.Format("{0} - {1}", currentEntity.Unused, currentEntity.Definition.ObjectName);
            }
        }

        private void entitiesList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (updateSelected) SelectedEntity?.Invoke(entities[entitiesList.SelectedIndex].Unused);
        }

        private void addProperty(LocalProperties properties, int category_index, string category, string name, string value_type, object value, bool read_only=false) {
            properties.Add(String.Format("{0}.{1}", category, name),
                    new LocalProperty(name, value_type, category_index, category, name, true, read_only, value, "")
                );
        }

        private void UpdateEntitiesProperties(List<RSDKv5.Scene.ISCN_Object> selectedEntities)
        {
            // TODO: Allow to change multiple entities
            /*bool first_entity = true;
            RSDKv5.SceneObject commonObject = null;

            foreach (var entity in selectedEntities)
            {
                if (first_entity) commonObject = entity.Object;
                else if (entity.Object != commonObject) commonObject = null;
            }

            if (commonObject != currentObject)
            {
                currentObject = commonObject;*/

            if (selectedEntities.Count != 1)
            {
                entityProperties.SelectedObject = null;
                currentEntity = null;
                entitiesList.ResetText();
                if (selectedEntities.Count > 1)
                {
                    entitiesList.SelectedText = String.Format("{0} entities selected", selectedEntities.Count);
                }
                return;
            }

            RSDKv5.Scene.ISCN_Object entity = selectedEntities[0];

            if (entity == currentEntity) return;
            currentEntity = entity;

            if (entitiesList.SelectedIndex >= 0 && entitiesList.SelectedIndex < entities.Count && entities[entitiesList.SelectedIndex] == currentEntity)
            {
                // Than it is called from selected item in the menu, so changeing the text will remove it, we don't want that
            }
            else
            {
                entitiesList.ResetText();
                entitiesList.SelectedText = String.Format("{0} - {1}", currentEntity.Unused, currentEntity.Definition.ObjectName);
                //entitiesList.SelectedIndex = entities.IndexOf(entity);
            }

            LocalProperties objProperties = new LocalProperties();
            int category_index = 2 + entity.Attributes.Count;
            addProperty(objProperties, category_index, "object", "name", "string", entity.Definition.ObjectName.ToString(), true);
            addProperty(objProperties, category_index, "object", "entitySlot", "ushort", entity.Unused, true);
            --category_index;
            addProperty(objProperties, category_index, "position", "x", "float", entity.X);
            addProperty(objProperties, category_index, "position", "y", "float", entity.Y);
            --category_index;

            int g = -1;
            foreach (var attribute in entity.Definition.AttributeTypes)
            {
                g++;
                string attribute_name = ""; // attribute.Name.ToString();
                var attribute_value = currentEntity.Attributes[g];
                switch (attribute)
                {
                    case (byte)RSDKv5.AttributeTypes.UINT8:
                        addProperty(objProperties, category_index, attribute_name, "uint8", "byte", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.UINT16:
                        addProperty(objProperties, category_index, attribute_name, "uint16", "ushort", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.UINT32:
                        addProperty(objProperties, category_index, attribute_name, "uint32", "uint", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.INT8:
                        addProperty(objProperties, category_index, attribute_name, "int8", "sbyte", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.INT16:
                        addProperty(objProperties, category_index, attribute_name, "int16", "short", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.INT32:
                        addProperty(objProperties, category_index, attribute_name, "int32", "int", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.VAR:
                        addProperty(objProperties, category_index, attribute_name, "var", "uint", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.BOOL:
                        addProperty(objProperties, category_index, attribute_name, "bool", "bool", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.STRING:
                        addProperty(objProperties, category_index, attribute_name, "string", "string", attribute_value);
                        break;
                    case (byte)RSDKv5.AttributeTypes.POSITION:
                        // addProperty(objProperties, category_index, attribute_name, "x", "float", attribute_value.X.High + ((float)attribute_value.ValuePosition.X.Low / 0x10000));
                        // addProperty(objProperties, category_index, attribute_name, "y", "float", attribute_value.ValuePosition.Y.High + ((float)attribute_value.ValuePosition.Y.Low / 0x10000));
                        break;
                    case (byte)RSDKv5.AttributeTypes.COLOR:
                        // var color = attribute_value.ValueColor;
                        // addProperty(objProperties, category_index, attribute_name, "color", "color", Color.FromArgb(255 /* color.A */, color.R, color.G, color.B));
                        break;
                }
                --category_index;
            }
            entityProperties.SelectedObject
                = new LocalPropertyGridObject(objProperties);
        }

        public void UpdateCurrentEntityProperites()
        {
            var obj = (entityProperties.SelectedObject as LocalPropertyGridObject);
            if (obj != null)
            {
                obj.setValue("position.x", currentEntity.X);
                obj.setValue("position.y", currentEntity.Y);
                int i = -1;
                foreach (var attribute in currentEntity.Definition.AttributeTypes)
                {
                    i++;
                    string attribute_name = ""; // attribute.Name.ToString();
                    // var attribute_value = currentEntity.GetAttribute(attribute_name);
                    var attribute_value = currentEntity.Attributes[i];
                    switch (attribute)
                    {
                        default:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "int32"), attribute_value);
                            break;
                        /*
                        case RSDKv5.AttributeTypes.UINT8:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "uint8"), attribute_value.ValueUInt8);
                            break;
                        case RSDKv5.AttributeTypes.UINT16:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "uint16"), attribute_value.ValueUInt16);
                            break;
                        case RSDKv5.AttributeTypes.UINT32:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "uint32"), attribute_value.ValueUInt32);
                            break;
                        case RSDKv5.AttributeTypes.INT8:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "int8"), attribute_value.ValueInt8);
                            break;
                        case RSDKv5.AttributeTypes.INT16:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "int16"), attribute_value.ValueInt16);
                            break;
                        case RSDKv5.AttributeTypes.INT32:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "int32"), attribute_value.ValueInt32);
                            break;
                        case RSDKv5.AttributeTypes.VAR:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "var"), attribute_value.ValueVar);
                            break;
                        case RSDKv5.AttributeTypes.BOOL:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "bool"), attribute_value.ValueBool);
                            break;
                        case RSDKv5.AttributeTypes.STRING:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "string"), attribute_value.ValueString);
                            break;
                        case RSDKv5.AttributeTypes.POSITION:
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "x"), attribute_value.ValuePosition.X.High + ((float)attribute_value.ValuePosition.X.Low / 0x10000));
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "y"), attribute_value.ValuePosition.Y.High + ((float)attribute_value.ValuePosition.Y.Low / 0x10000));
                            break;
                        case RSDKv5.AttributeTypes.COLOR:
                            var color = attribute_value.ValueColor;
                            obj.setValue(String.Format("{0}.{1}", attribute_name, "color"), Color.FromArgb(255 + 0 * color.A, color.R, color.G, color.B));
                            break;
                        //*/
                    }
                }
                NeedRefresh = true;
            }
        }

        public void PropertiesRefresh()
        {
            entityProperties.Refresh();
            NeedRefresh = false;
        }
        private void setEntitiyProperty(RSDKv5.Scene.ISCN_Object entity, string tag, object value, object oldValue)
        {
            string[] parts = tag.Split('.');
            string category = parts[0];
            string name = parts[1];
            if (category == "position")
            {
                float fvalue = (float)value;
                if (fvalue < Int16.MinValue || fvalue > Int16.MaxValue)
                {
                    // Invalid
                    var obj = (entityProperties.SelectedObject as LocalPropertyGridObject);
                    obj.setValue(tag, oldValue);
                    return;
                }
                //var pos = entity.Position;
                if (name == "x")
                {
                    entity.X = (short)fvalue;
                }
                else if (name == "y")
                {
                    entity.Y = (short)fvalue;
                }
                if (entity == currentEntity)
                    UpdateCurrentEntityProperites();
            }
            else
            {
                /*
                var attribute = entity.Attributes(category);
                switch (attribute.Type)
                {
                    case RSDKv5.AttributeTypes.UINT8:
                        attribute.ValueUInt8 = (byte)value;
                        break;
                    case RSDKv5.AttributeTypes.UINT16:
                        attribute.ValueUInt16 = (ushort)value;
                        break;
                    case RSDKv5.AttributeTypes.UINT32:
                        attribute.ValueUInt32 = (uint)value;
                        break;
                    case RSDKv5.AttributeTypes.INT8:
                        attribute.ValueInt8 = (sbyte)value;
                        break;
                    case RSDKv5.AttributeTypes.INT16:
                        attribute.ValueInt16 = (short)value;
                        break;
                    case RSDKv5.AttributeTypes.INT32:
                        attribute.ValueInt32 = (int)value;
                        break;
                    case RSDKv5.AttributeTypes.VAR:
                        attribute.ValueVar = (uint)value;
                        break;
                    case RSDKv5.AttributeTypes.BOOL:
                        attribute.ValueBool = (bool)value;
                        break;
                    case RSDKv5.AttributeTypes.STRING:
                        attribute.ValueString = (string)value;
                        break;
                    case RSDKv5.AttributeTypes.POSITION:
                        float fvalue = (float)value;
                        if (fvalue < Int16.MinValue || fvalue > Int16.MaxValue)
                        {
                            // Invalid
                            var obj = (entityProperties.SelectedObject as LocalPropertyGridObject);
                            obj.setValue(tag, oldValue);
                            return;
                        }
                        var pos = attribute.ValuePosition;
                        if (name == "x")
                        {
                            pos.X.High = (short)fvalue;
                            pos.X.Low = (ushort)(fvalue * 0x10000);
                        }
                        else if (name == "y")
                        {
                            pos.Y.High = (short)fvalue;
                            pos.Y.Low = (ushort)(fvalue * 0x10000);
                        }
                        attribute.ValuePosition = pos;
                        if (entity == currentEntity)
                            UpdateCurrentEntityProperites();
                        break;
                    case RSDKv5.AttributeTypes.COLOR:
                        Color c = (Color)value;
                        attribute.ValueColor = new RSDKv5.Color(c.R, c.G, c.B, c.A);
                        break;
                }
                //*/
            }
        }


        private void entityProperties_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            string tag = e.ChangedItem.PropertyDescriptor.Name;
            AddAction?.Invoke(new Actions.ActionEntityPropertyChange(currentEntity, tag, e.OldValue, e.ChangedItem.Value, new Action<RSDKv5.Scene.ISCN_Object, string, object, object>(setEntitiyProperty)));
            setEntitiyProperty(currentEntity, tag, e.ChangedItem.Value, e.OldValue);
        }

        private void entitiesList_DropDown(object sender, EventArgs e)
        {
            // It is slow to update the list, so lets generate it when the menu opens
            entitiesList.Items.Clear();
            entitiesList.Items.AddRange(entities.Select(x => String.Format("{0} - {1}", x.Unused, x.Definition.ObjectName)).ToArray());
        }
    }
}
