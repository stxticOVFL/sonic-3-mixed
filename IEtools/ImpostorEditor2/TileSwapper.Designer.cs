namespace ImpostorEditor2 {
    partial class TileSwapper {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.tilesList1 = new ImpostorEditor2.TilesList();
            this.tilesList2 = new ImpostorEditor2.TilesList();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.tilesList1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.tilesList2);
            this.splitContainer1.Size = new System.Drawing.Size(1264, 450);
            this.splitContainer1.SplitterDistance = 632;
            this.splitContainer1.TabIndex = 1;
            // 
            // tilesList1
            // 
            this.tilesList1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tilesList1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tilesList1.FlipHorizontal = false;
            this.tilesList1.FlipVertical = false;
            this.tilesList1.Location = new System.Drawing.Point(0, 0);
            this.tilesList1.Name = "tilesList1";
            this.tilesList1.Size = new System.Drawing.Size(632, 450);
            this.tilesList1.TabIndex = 0;
            this.tilesList1.TileScale = 2;
            // 
            // tilesList2
            // 
            this.tilesList2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tilesList2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tilesList2.FlipHorizontal = false;
            this.tilesList2.FlipVertical = false;
            this.tilesList2.Location = new System.Drawing.Point(0, 0);
            this.tilesList2.Name = "tilesList2";
            this.tilesList2.Size = new System.Drawing.Size(628, 450);
            this.tilesList2.TabIndex = 0;
            this.tilesList2.TileScale = 2;
            // 
            // TileSwapper
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 450);
            this.Controls.Add(this.splitContainer1);
            this.Name = "TileSwapper";
            this.ShowIcon = false;
            this.Text = "TileSwapper";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.SplitContainer splitContainer1;
        public TilesList tilesList1;
        public TilesList tilesList2;
    }
}