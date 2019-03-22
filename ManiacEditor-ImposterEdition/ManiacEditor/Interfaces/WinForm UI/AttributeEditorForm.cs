using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ManiacEditor
{
    public partial class AttributeEditorForm : Form
    {

        public RSDKv5.Scene Scene = new RSDKv5.Scene();
        public int SceneObjectID = 0;

        int CurAttribute = 0;

        string Filename;

        public AttributeEditorForm()
        {
            InitializeComponent();
            Filename = "";
        }

        public void Setup()
        {
            RefreshObjList();
            RefreshList();
            RefreshUI();
        }

        public AttributeEditorForm(RSDKv5.Scene S, int OID)
        {
            InitializeComponent();
            Scene = S;
            SceneObjectID = OID;
            RefreshList();
            RefreshUI();
        }

        private void AttributesBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (AttributesBox.SelectedIndex >= 0)
            {
                CurAttribute = AttributesBox.SelectedIndex;
                RefreshUI();
            }
        }

        public void RefreshUI()
        {
            if (Scene.Objects.Count > 0 && SceneObjectID < Scene.Objects.Count)
            {
                OBJNameBox.Text = Scene.Objects[SceneObjectID].Name.Name;
                if (Scene.Objects[SceneObjectID].Attributes.Count > 0 && CurAttribute >= 0)
                {
                    ANameBox.Text = Scene.Objects[SceneObjectID].Attributes[CurAttribute].Name.Name;
                    ATypeBox.SelectedIndex = (byte)Scene.Objects[SceneObjectID].Attributes[CurAttribute].Type;
                }
            }
        }

        public void RefreshList()
        {
            AttributesBox.Items.Clear();
            if (Scene.Objects.Count > 0 && SceneObjectID < Scene.Objects.Count)
            {
                for (int i = 0; i < Scene.Objects[SceneObjectID].Attributes.Count; i++)
                {
                    AttributesBox.Items.Add(Scene.Objects[SceneObjectID].Attributes[i].Name);
                }
            }
        }

        public void RefreshObjList()
        {
            ObjectList.Items.Clear();
            if (Scene.Objects.Count > 0)
            {
                for (int i = 0; i < Scene.Objects.Count; i++)
                {
                    ObjectList.Items.Add(Scene.Objects[i].Name);
                }
            }
        }

        private void ANameBox_TextChanged(object sender, EventArgs e)
        {
            if (Scene.Objects[SceneObjectID].Attributes.Count > 0)
            {
                Scene.Objects[SceneObjectID].Attributes[CurAttribute].Name = new RSDKv5.NameIdentifier(ANameBox.Text);
                AttributesBox.Items[CurAttribute] = Scene.Objects[SceneObjectID].Attributes[CurAttribute].Name;
            }
        }

        private void ATypeBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Scene.Objects[SceneObjectID].Attributes.Count > 0)
            {
                Scene.Objects[SceneObjectID].Attributes[CurAttribute].Type = (RSDKv5.AttributeTypes)ATypeBox.SelectedIndex;
            }
        }

        private void addAttributeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Scene.Objects[SceneObjectID].Attributes.Add(new RSDKv5.AttributeInfo());
            if (CurAttribute > 0 && CurAttribute >= 0)
            {
                CurAttribute++;
            }
            RefreshList();
            RefreshUI();
        }

        private void removeAttributeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (Scene.Objects[SceneObjectID].Attributes.Count > 0 && CurAttribute >= 0)
            {
                Scene.Objects[SceneObjectID].Attributes.RemoveAt(CurAttribute);
                CurAttribute--;
                RefreshList();
                RefreshUI();
            }
        }

        private void OBJNameBox_TextChanged(object sender, EventArgs e)
        {
            Scene.Objects[SceneObjectID].Name = new RSDKv5.NameIdentifier(OBJNameBox.Text);
        }

        private void AttributeEditorForm_Close(object sender, FormClosedEventArgs e)
        {
            DialogResult = DialogResult.OK;
        }

        private void ObjectList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ObjectList.SelectedIndex < 0) ObjectList.SelectedIndex = 0;
            SceneObjectID = ObjectList.SelectedIndex;
            RefreshList();
            RefreshUI();
        }

        private void AttributeEditorForm_Load(object sender, EventArgs e)
        {

        }

        private void addObjectToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Scene.Objects.Add(new RSDKv5.SceneObject());
            RefreshObjList();
            RefreshList();
            RefreshUI();
        }

        private void removeObjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Scene.Objects.RemoveAt(SceneObjectID);
            RefreshObjList();
            RefreshList();
            RefreshUI();
        }
    }
}
