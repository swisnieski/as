using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace As
{
    [Description("BinCtl")]
    public partial class BinCtl : Control
    {
        //
        // set default values
        //
        private int _Separators = 1;
        private int _ValMan = 0;
        private int _Number = 0;
        private double _Maximum = 1;
        private double _Value = 5;
        private double _Inv = 10;
        private double _Target = 10;
        private bool _Metric = false;
        private bool _Idle = false;
        private bool _Tol = false;
        private bool _Open = false;
        private bool _Empty = false;
        private bool _ScaleInLB = false;        //DC 3.2.0
        private bool _Delay = false;            //DC 4.0.0
        private int _Count = 0;                 //DC 4.0.0
        private bool _Add = false;              //DC 4.0.0
        private bool _DisableInv = false;       //DC 4.0.1

        private Color _BarColor = Color.FromArgb(255, 128, 128);
        private Color _BorderColor = Color.Black;

        public BinCtl()
        {
            base.Size = new Size(60, 120);
  //          base.Font.Size = 10.0F;
            
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.ResizeRedraw |
                ControlStyles.DoubleBuffer,
                true
                );
        }

        [Description("BinCtl Open")]
        [Category("BinCtl")]
        public bool Open
        {
            get
            {
                return _Open;
            }
            set
            {
                _Open = value;
                this.Invalidate();
            }
        }
        [Description("BinCtl Empty")]
        [Category("BinCtl")]
        public bool Empty
        {
            get
            {
                return _Empty;
            }
            set
            {
                _Empty = value;
                this.Invalidate();
            }
        }
        [Description("BinCtl ScaleInLB")]
        [Category("BinCtl")]
        public bool ScaleInLB
        {
            get
            {
                return _ScaleInLB;
            }
            set
            {
                _ScaleInLB = value;
                this.Invalidate();
            }
        }
        [Description("BinCtl Delay")]
        [Category("BinCtl")]
        public bool Delay
        {
            get
            {
                return _Delay;
            }
            set
            {
                _Delay = value;
                this.Invalidate();
            }
        }
        [Description("BinCtl Add")]
        [Category("BinCtl")]
        public bool Add
        {
            get
            {
                return _Add;
            }
            set
            {
                _Add = value;
                this.Invalidate();
            }
        }
        [Description("BinCtl Disable Inv")]
        [Category("BinCtl")]
        public bool DisableInv
        {
            get
            {
                return _DisableInv;
            }
            set
            {
                _DisableInv = value;
                this.Invalidate();
            }
        }
        [Description("The border color of BinCtl")]
        [Category("BinCtl")]
        public Color BorderColor
        {
            get
            {
                return _BorderColor;
            }
            set
            {
                _BorderColor = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Maximum")]
        [Category("BinCtl")]
        public double Maximum
        {
            get
            {
                return _Maximum;
            }
            set
            {
                if (value < 1)
                    value = 1;
                _Maximum = value;
                this.Invalidate();
            }
        }
        [Description("The current value for Bar, ")]
        [Category("BinCtl")]
        // the rest of the Properties windows must be updated when this peroperty is changed.
        [RefreshProperties(RefreshProperties.All)]
        public double Value
        {
            get
            {
                return _Value;
            }
            set
            {
                if (value > _Maximum)
                    value = _Maximum;

                _Value = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Inventory")]
        [Category("BinCtl")]
        public double Inventory
        {
            get
            {
                return _Inv;
            }
            set
            {
                _Inv = value;
                this.Invalidate();
            }
        }
        [Description("BinCtl Target")]
        [Category("BinCtl")]
        public double Target
        {
            get
            {
                return _Target;
            }
            set
            {
                _Target = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl ValMan")]
        [Category("BinCtl")]
        public int ValMan
        {
            get
            {
                return _ValMan;
            }
            set
            {
                _ValMan = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Number")]
        [Category("BinCtl")]
        public int Number
        {
            get
            {
                return _Number;
            }
            set
            {
                _Number = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Count")]
        [Category("BinCtl")]
        public int Count
        {
            get
            {
                return _Count;
            }
            set
            {
                _Count = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Metric")]
        [Category("BinCtl")]
        public bool Metric
        {
            get
            {
                return _Metric;
            }
            set
            {
                _Metric = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Idle")]
        [Category("BinCtl")]
        public bool Idle
        {
            get
            {
                return _Idle;
            }
            set
            {
                _Idle = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl Tolerance")]
        [Category("BinCtl")]
        public bool Tol
        {
            get
            {
                return _Tol;
            }
            set
            {
                _Tol = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl number of Separators")]
        [Category("BinCtl")]
        public int Separators
        {
            get
            {
                return _Separators;
            }
            set
            {
                _Separators = value;
                this.Invalidate();
            }
        }

        [Description("BinCtl color")]
        [Category("BinCtl")]
        public Color BarColor
        {
            get
            {
                return _BarColor;
            }
            set
            {
                _BarColor = value;
                this.Invalidate();
            }
        }

        //---------------------------------------------------------------------
        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            int fillHeight = 0;
            Rectangle leftRect;
            Rectangle rightRect;
            Rectangle botRect;
            Rectangle topRect;
            int h1 = 20, h2;
            Color liteColor = ControlPaint.LightLight(_BarColor);
            Color darkColor = ControlPaint.Dark(_BarColor);
            Color topColor;
            double valPos = _Value;

            if (valPos < 0)
                valPos = 0;

            // Calculate matching colors
            if (!_Idle)
            {
                topColor = darkColor;         // Color.Black;
            }
            else
            {
                topColor = darkColor = liteColor = _BorderColor = _BarColor;

                if (this.Text.Length > 0)
                    topColor = ControlPaint.Dark(_BarColor);
            }

            // The following is the height of the bar. This will vary with each value.
            h2 = this.Height - h1 * 2;
            fillHeight = (int)((h2 * (_Maximum - valPos)) / _Maximum);

 //           if (!_Idle)
            {
                // Fill top rectangle
                SolidBrush xBrush = new SolidBrush(topColor);
  //              SolidBrush xBrush = new SolidBrush(Color.Black);
                topRect = new Rectangle(0, h1, this.Width, h1 * 5 / 2);
                e.Graphics.FillRectangle(xBrush, topRect);
                xBrush.Dispose();
            }

            if (fillHeight > 0)
            {
                // Rectangles for left and right half of bar
                leftRect = new Rectangle(0, h1*5/2, this.Width / 2, fillHeight-h1*3/2);
                rightRect = new Rectangle(this.Width / 2, h1*5/2, Width / 2, fillHeight-h1*3/2);

                // The gradient brush
                LinearGradientBrush brush;

                // Paint left box
                brush = new LinearGradientBrush(new Point(0, 0),
                            new Point(this.Width / 2, 0), darkColor, _BarColor);

                e.Graphics.FillRectangle(brush, leftRect);
                brush.Dispose();

                // Paint right box
                // (this.Height/2 - 1 because there would be a dark line in the middle of the bar)
                brush = new LinearGradientBrush(new Point(this.Width / 2 - 1, 0),
                          new Point(this.Width, 0), _BarColor, darkColor);

                e.Graphics.FillRectangle(brush, rightRect);
                brush.Dispose();
            }

            // Fill bottom rectangle
            SolidBrush bgBrush = new SolidBrush(darkColor);
            botRect = new Rectangle(0, fillHeight + h1, this.Width, h2 - fillHeight);
            e.Graphics.FillRectangle(bgBrush, botRect);
            bgBrush.Dispose();

            //
            // Paint separators -----------------------------------------------
            //
            int sepHeight;
            int sepInc;
            Color sepColor;

            if (!_Idle)
            {
                sepHeight = sepInc = h2 / (_Separators + 1);

                // Draw each separator line
                for (int i = 1; i <= _Separators; i++)
                {
                    if (sepHeight >= fillHeight)
                        sepColor = liteColor;
                    else
                        sepColor = darkColor;
                    e.Graphics.DrawLine(new Pen(sepColor, 1), 0, h1 + sepHeight,
                                                     this.Width, h1 + sepHeight);
                    sepHeight += sepInc;
                }
            }
            // draw text-------------------------------------------------------
            SolidBrush tBrush;
            SolidBrush iBrush;
            SolidBrush vBrush;
            SolidBrush mBrush = new SolidBrush(Color.Cyan);
            SolidBrush wBrush = new SolidBrush(Color.White);
            SolidBrush bBrush = new SolidBrush(Color.Black);
            Font pFont = new Font("Arial", 16.0F, FontStyle.Bold);
            Font pFont1 = new Font("Arial", 24.0F, FontStyle.Bold);
            //           double v;

            if (_Target > 0)
                tBrush = new SolidBrush(Color.Black);
            else
                tBrush = new SolidBrush(Color.DimGray);

            if (_Inv >= 0)
            {
                if(_Metric)
                    iBrush = new SolidBrush(Color.Yellow);
                else
                    iBrush = new SolidBrush(Color.White);
            }
            else
                iBrush = new SolidBrush(Color.Red);

            if (_Tol)
                vBrush = new SolidBrush(Color.Red);
            else
                vBrush = new SolidBrush(Color.Black);

            e.Graphics.DrawString(Text, this.Font, tBrush, 0.0F, 0.0F);

            if(_Number > 0)
                e.Graphics.DrawString(_Number.ToString(), pFont1, bBrush, 20.0F, 100.0F);

            if (_ScaleInLB)
            {
                if (_Inv != 0 && !_DisableInv)
                    e.Graphics.DrawString(_Inv.ToString("F00"), pFont, iBrush, 5.0F, (float)(h1 + 5));

                if (_Target > 0)
                    e.Graphics.DrawString(_Target.ToString("F00"), pFont, iBrush, (float)(h1 - 12), (float)h2 - 10);
            }
            else
            {
                if (_Inv != 0 && !_DisableInv)
                    e.Graphics.DrawString(_Inv.ToString("F01"), pFont, iBrush, 5.0F, (float)(h1 + 5));

                if (_Target > 0)
                    e.Graphics.DrawString(_Target.ToString("F02"), pFont, iBrush, (float)(h1 - 12), (float)h2 - 10);
            }

            if (_ValMan > 0)
                e.Graphics.DrawString(_ValMan.ToString(), this.Font, mBrush, (float)(h1 + 1), (float)h2);

 //           if (_Value != 0)
   //         {
     //           v = -_Value;
       //         e.Graphics.DrawString(v.ToString("F02"), this.Font, vBrush, (float)(h1 + 1), (float)(h1 + 2 + h2));
         //   }

            if (_Empty)
                e.Graphics.DrawString("EMPTY", this.Font, wBrush, 7.0F, (float)h2-18.0F);

            //DC 4.0.0
            if (_Delay)
                e.Graphics.DrawString("SETTLE", this.Font, wBrush, 6.0F, (float)h2 - 45.0F);
            if (_Count > 0)
                e.Graphics.DrawString(_Count.ToString(), this.Font, wBrush, 64.0F, (float)h2 - 45.0F);
            if (_Add)
                e.Graphics.DrawString("Add", this.Font, wBrush, 7.0F, (float)h2 - 45.0F);

            tBrush.Dispose();
            iBrush.Dispose();
            vBrush.Dispose();
            wBrush.Dispose();
            mBrush.Dispose();
            bBrush.Dispose();

            //
            // Draw border ----------------------------------------------------
            //
            Pen pen = new Pen(_BorderColor, 3);
            Rectangle borderRect = new Rectangle(0, h1, 
                this.Width - 1, h2 - 1);
 
            e.Graphics.DrawRectangle(pen, borderRect);

            if (!_Open)
            {
                e.Graphics.DrawLine(pen, 2, this.Height - h1, h1+2, this.Height);
                e.Graphics.DrawLine(pen, this.Width -2, this.Height - h1, this.Width - h1 -2, this.Height);
                e.Graphics.DrawLine(pen, h1, this.Height-2, this.Width - h1, this.Height-2);
            }
            else
            {
                e.Graphics.DrawLine(pen, 2, this.Height - h1, 2, this.Height);
                e.Graphics.DrawLine(pen, this.Width - 2, this.Height - h1, this.Width - 2, this.Height);
//                e.Graphics.DrawLine(pen, h1, this.Height - 2, this.Width - h1, this.Height - 2);
            }
        }
    }
}