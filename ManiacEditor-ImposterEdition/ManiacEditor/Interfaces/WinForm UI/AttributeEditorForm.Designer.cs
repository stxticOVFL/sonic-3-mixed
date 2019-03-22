namespace ManiacEditor
{
    partial class AttributeEditorForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.aToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.reToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.AttributesBox = new System.Windows.Forms.ListBox();
            this.ObjectNameBox = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.OBJNameBox = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ATypeBox = new System.Windows.Forms.ComboBox();
            this.ATypeLabel = new System.Windows.Forms.Label();
            this.ANameBox = new System.Windows.Forms.TextBox();
            this.ANameLabel = new System.Windows.Forms.Label();
            this.ObjectList = new System.Windows.Forms.ListBox();
            this.addObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addObjectToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.removeObjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.ObjectNameBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aToolStripMenuItem,
            this.reToolStripMenuItem,
            this.addObjectToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(436, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // aToolStripMenuItem
            // 
            this.aToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.aToolStripMenuItem.Name = "aToolStripMenuItem";
            this.aToolStripMenuItem.Size = new System.Drawing.Size(112, 24);
            this.aToolStripMenuItem.Text = "Add Attribute";
            this.aToolStripMenuItem.Click += new System.EventHandler(this.addAttributeToolStripMenuItem_Click);
            // 
            // reToolStripMenuItem
            // 
            this.reToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.reToolStripMenuItem.Name = "reToolStripMenuItem";
            this.reToolStripMenuItem.Size = new System.Drawing.Size(138, 24);
            this.reToolStripMenuItem.Text = "Remove Attribute";
            this.reToolStripMenuItem.Click += new System.EventHandler(this.removeAttributeToolStripMenuItem_Click);
            // 
            // AttributesBox
            // 
            this.AttributesBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(36)))), ((int)(((byte)(36)))), ((int)(((byte)(36)))));
            this.AttributesBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.AttributesBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.AttributesBox.FormattingEnabled = true;
            this.AttributesBox.ItemHeight = 16;
            this.AttributesBox.Location = new System.Drawing.Point(0, 28);
            this.AttributesBox.Name = "AttributesBox";
            this.AttributesBox.Size = new System.Drawing.Size(126, 303);
            this.AttributesBox.TabIndex = 30;
            this.AttributesBox.SelectedIndexChanged += new System.EventHandler(this.AttributesBox_SelectedIndexChanged);
            // 
            // ObjectNameBox
            // 
            this.ObjectNameBox.Controls.Add(this.label1);
            this.ObjectNameBox.Controls.Add(this.OBJNameBox);
            this.ObjectNameBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.ObjectNameBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ObjectNameBox.Location = new System.Drawing.Point(126, 28);
            this.ObjectNameBox.Name = "ObjectNameBox";
            this.ObjectNameBox.Size = new System.Drawing.Size(310, 74);
            this.ObjectNameBox.TabIndex = 31;
            this.ObjectNameBox.TabStop = false;
            this.ObjectNameBox.Text = "Object Data:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 17);
            this.label1.TabIndex = 26;
            this.label1.Text = "Object Name:";
            // 
            // OBJNameBox
            // 
            this.OBJNameBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.OBJNameBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.OBJNameBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.OBJNameBox.Location = new System.Drawing.Point(12, 38);
            this.OBJNameBox.Name = "OBJNameBox";
            this.OBJNameBox.Size = new System.Drawing.Size(292, 22);
            this.OBJNameBox.TabIndex = 25;
            this.OBJNameBox.TextChanged += new System.EventHandler(this.OBJNameBox_TextChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ATypeBox);
            this.groupBox1.Controls.Add(this.ATypeLabel);
            this.groupBox1.Controls.Add(this.ANameBox);
            this.groupBox1.Controls.Add(this.ANameLabel);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.groupBox1.Location = new System.Drawing.Point(126, 102);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(310, 107);
            this.groupBox1.TabIndex = 33;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Attribute Data";
            // 
            // ATypeBox
            // 
            this.ATypeBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ATypeBox.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ATypeBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ATypeBox.FormattingEnabled = true;
            this.ATypeBox.Items.AddRange(new object[] {
            "UINT8",
            "UINT16",
            "UINT32",
            "INT8",
            "INT16",
            "INT32",
            "VAR",
            "BOOL",
            "STRING",
            "VECTOR2",
            "UNKNOWN",
            "COLOUR",});
            this.ATypeBox.Location = new System.Drawing.Point(123, 65);
            this.ATypeBox.Name = "ATypeBox";
            this.ATypeBox.Size = new System.Drawing.Size(178, 24);
            this.ATypeBox.TabIndex = 32;
            this.ATypeBox.SelectedIndexChanged += new System.EventHandler(this.ATypeBox_SelectedIndexChanged);
            // 
            // ATypeLabel
            // 
            this.ATypeLabel.AutoSize = true;
            this.ATypeLabel.Location = new System.Drawing.Point(10, 72);
            this.ATypeLabel.Name = "ATypeLabel";
            this.ATypeLabel.Size = new System.Drawing.Size(101, 17);
            this.ATypeLabel.TabIndex = 31;
            this.ATypeLabel.Text = "Attribute Type:";
            // 
            // ANameBox
            // 
            this.ANameBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ANameBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ANameBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ANameBox.Location = new System.Drawing.Point(123, 28);
            this.ANameBox.Name = "ANameBox";
            this.ANameBox.Size = new System.Drawing.Size(178, 22);
            this.ANameBox.TabIndex = 30;
            this.ANameBox.TextChanged += new System.EventHandler(this.ANameBox_TextChanged);
            // 
            // ANameLabel
            // 
            this.ANameLabel.AutoSize = true;
            this.ANameLabel.Location = new System.Drawing.Point(10, 28);
            this.ANameLabel.Name = "ANameLabel";
            this.ANameLabel.Size = new System.Drawing.Size(106, 17);
            this.ANameLabel.TabIndex = 29;
            this.ANameLabel.Text = "Attribute Name:";
            // 
            // ObjectList
            // 
            this.ObjectList.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(36)))), ((int)(((byte)(36)))), ((int)(((byte)(36)))));
            this.ObjectList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ObjectList.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ObjectList.FormattingEnabled = true;
            this.ObjectList.ItemHeight = 16;
            this.ObjectList.Location = new System.Drawing.Point(126, 209);
            this.ObjectList.Name = "ObjectList";
            this.ObjectList.Size = new System.Drawing.Size(310, 122);
            this.ObjectList.TabIndex = 34;
            this.ObjectList.SelectedIndexChanged += new System.EventHandler(this.ObjectList_SelectedIndexChanged);
            // 
            // addObjectToolStripMenuItem
            // 
            this.addObjectToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addObjectToolStripMenuItem1,
            this.removeObjectToolStripMenuItem});
            this.addObjectToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.addObjectToolStripMenuItem.Name = "addObjectToolStripMenuItem";
            this.addObjectToolStripMenuItem.Size = new System.Drawing.Size(116, 24);
            this.addObjectToolStripMenuItem.Text = "Object Editing";
            // 
            // addObjectToolStripMenuItem1
            // 
            this.addObjectToolStripMenuItem1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.addObjectToolStripMenuItem1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.addObjectToolStripMenuItem1.Name = "addObjectToolStripMenuItem1";
            this.addObjectToolStripMenuItem1.Size = new System.Drawing.Size(216, 26);
            this.addObjectToolStripMenuItem1.Text = "Add Object";
            this.addObjectToolStripMenuItem1.Click += new System.EventHandler(this.addObjectToolStripMenuItem1_Click);
            // 
            // removeObjectToolStripMenuItem
            // 
            this.removeObjectToolStripMenuItem.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.removeObjectToolStripMenuItem.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.removeObjectToolStripMenuItem.Name = "removeObjectToolStripMenuItem";
            this.removeObjectToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.removeObjectToolStripMenuItem.Text = "Remove Object";
            this.removeObjectToolStripMenuItem.Click += new System.EventHandler(this.removeObjectToolStripMenuItem_Click);
            // 
            // AttributeEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(48)))), ((int)(((byte)(48)))), ((int)(((byte)(48)))));
            this.ClientSize = new System.Drawing.Size(436, 331);
            this.Controls.Add(this.ObjectList);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.ObjectNameBox);
            this.Controls.Add(this.AttributesBox);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "AttributeEditorForm";
            this.Text = "Object Attributes";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.AttributeEditorForm_Close);
            this.Load += new System.EventHandler(this.AttributeEditorForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ObjectNameBox.ResumeLayout(false);
            this.ObjectNameBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem aToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reToolStripMenuItem;
        private System.Windows.Forms.ListBox AttributesBox;
        private System.Windows.Forms.GroupBox ObjectNameBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox OBJNameBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox ATypeBox;
        private System.Windows.Forms.Label ATypeLabel;
        private System.Windows.Forms.TextBox ANameBox;
        private System.Windows.Forms.Label ANameLabel;
        private System.Windows.Forms.ListBox ObjectList;
        private System.Windows.Forms.ToolStripMenuItem addObjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addObjectToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem removeObjectToolStripMenuItem;
    }
}