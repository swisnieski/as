using System;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Security.Permissions;

// Without Unrestricted=true or Read or Write, this permission request 
// is incomplete, and cannot be enforced.
//[assembly: FileIOPermission(SecurityAction.RequestMinimum)]
[assembly: CLSCompliant(true)]

namespace As
{
    [Description("BarCtl")]
    [ToolboxBitmap(typeof(ProgressBar))]
    [Designer(typeof(BarCtlDesigner))]
    public class BarCtl : System.Windows.Forms.Control
    {

        //
        // set default values
        //
        private bool _Vertical = false;
        private int _Separators = 0;
        private double _Maximum = 100;
        private double _Value = 50;
        private double _Target = 10;
        private int _Flow = 0;
        private bool _ScaleInLB = false;    //DC 3.2.0
        private int _Pct = 0;               //DC 4.0.0


        private FillStyles _FillStyle = FillStyles.Dashed;
        private Color _BarColor = Color.FromArgb(255, 128, 128);
        private Color _BorderColor = Color.Black;

        public enum FillStyles
        {
            Solid,
            Dashed,
            Flat
        }

        public BarCtl()
        {
            base.Size = new Size(20, 100);
 //           base.Font.Size = 10.0F;
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.ResizeRedraw |
                ControlStyles.DoubleBuffer,
                true
                );
        }

        [Description("BarCtl number of Separators")]
        [Category("BarCtl")]
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

        [Description("BarCtl Vertical")]
        [Category("BarCtl")]
        public bool Vertical
        {
            get
            {
                return _Vertical;
            }
            set
            {
                _Vertical = value;
                this.Invalidate();
            }
        }

        [Description("BarCtl ScaleInLB")]
        [Category("BarCtl")]
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

        [Description("BarCtl color")]
        [Category("BarCtl")]
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

        [Description("BarCtl fill style")]
        [Category("BarCtl")]
        public FillStyles FillStyle
        {
            get
            {
                return _FillStyle;
            }
            set
            {
                _FillStyle = value;
                this.Invalidate();
            }
        }

        [Description("The current value for the BarCtl")]
        [Category("BarCtl")]
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
                if (value < 0)
                    value = 0;

                if (value > _Maximum)
                    value = _Maximum;

                _Value = value;
                this.Invalidate();
            }
        }

        [Description("The uppper bound of BarCtl")]
        [Category("BarCtl")]
        [RefreshProperties(RefreshProperties.All)]
        public double Maximum
        {
            get
            {
                return _Maximum;
            }
            set
            {
                _Maximum = value;

                if (_Maximum < 1)
                    _Maximum = 1;

                this.Invalidate();
            }
        }

        [Description("BarCtl Target")]
        [Category("BarCtl")]
        public double Target
        {
            get
            {
                return _Target;
            }
            set
            {
                if (value > _Maximum)
                    value = _Maximum;
                _Target = value;
                this.Invalidate();
            }
        }

        [Description("BarCtl Flow")]
        [Category("BarCtl")]
        public int Flow
        {
            get
            {
                return _Flow;
            }
            set
            {
                _Flow = value;
                this.Invalidate();
            }
        }
        [Description("BarCtl Pct")]
        [Category("BarCtl")]
        public int Pct
        {
            get
            {
                return _Pct;
            }
            set
            {
                _Pct = value;
                this.Invalidate();
            }
        }

        [Description("The border color of BarCtl")]
        [Category("BarCtl")]
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

        //---------------------------------------------------------------------
        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            int fillHeight = 0;
            int fillWidth = 0;
            Rectangle topRect;
            Rectangle botRect;
            Rectangle leftRect;
            Rectangle rightRect;
            Rectangle lowRect;
            int w2 = 0;

            Color darkColor = ControlPaint.Dark(_BarColor);
            Color liteColor = ControlPaint.LightLight(_BarColor);

            // The following is the width of the bar. This will vary with each value.
            if (_Vertical)
            {
                fillHeight = (int)(this.Height * (_Maximum - _Value) / _Maximum);

                // Rectangles for upper and lower half of bar
                leftRect = new Rectangle(0, 0, this.Width / 2, fillHeight);
                rightRect = new Rectangle(this.Width / 2, 0, Width / 2, fillHeight);
                lowRect = new Rectangle(0, fillHeight, Width, Height);

                if (_FillStyle == FillStyles.Flat)
                {
                    SolidBrush brush = new SolidBrush(liteColor);
                    e.Graphics.FillRectangle(brush, leftRect);
                    e.Graphics.FillRectangle(brush, rightRect);
                    brush.Dispose();
                }
                // The gradient brush
                else
                {
                    LinearGradientBrush brush;

                    // Paint upper half
                    brush = new LinearGradientBrush(new Point(0, 0),
                                new Point(this.Width / 2, 0), darkColor, _BarColor);
                    e.Graphics.FillRectangle(brush, leftRect);
                    brush.Dispose();

                    // Paint lower half
                    // (this.Height/2 - 1 because there would be a dark line in the middle of the bar)
                    brush = new LinearGradientBrush(new Point(this.Width / 2 - 1, 0),
                              new Point(this.Width, 0), _BarColor, darkColor);
                    e.Graphics.FillRectangle(brush, rightRect);
                    brush.Dispose();
                }
                // solid, dark brush
                SolidBrush bbrush = new SolidBrush(darkColor);
                e.Graphics.FillRectangle(bbrush, lowRect);
                bbrush.Dispose();

            }
            // horizontal -----------------------------------------------------
            else
            {
                fillWidth = (int)((this.Width-w2) * _Value / _Maximum);
                int hh = this.Height / 2;

                // Rectangles for upper and lower half of bar
                topRect = new Rectangle(fillWidth, 0, Width-w2-fillWidth, hh);
                botRect = new Rectangle(fillWidth, hh, Width - w2 - fillWidth, this.Height);
                leftRect = new Rectangle(0, 0, fillWidth, this.Height);

                if (_FillStyle == FillStyles.Flat)
                {
                    SolidBrush brush = new SolidBrush(darkColor);
                    e.Graphics.FillRectangle(brush, topRect);
                    e.Graphics.FillRectangle(brush, botRect);
                    brush.Dispose();
                }
                else
                {
                    // solid, dark brush
                    SolidBrush bbrush = new SolidBrush(darkColor);
                    e.Graphics.FillRectangle(bbrush, leftRect);
                    bbrush.Dispose();

                    // The gradient brush
                    LinearGradientBrush brush;

                    // Paint upper half
                    brush = new LinearGradientBrush(new Point(0, 0),
                                new Point(0, hh), darkColor, _BarColor);

                    e.Graphics.FillRectangle(brush, topRect);
                    brush.Dispose();

                    // Paint lower half
                    // (this.Height/2 - 1 because there would be a dark line in the middle of the bar)
                    //
                    brush = new LinearGradientBrush(new Point(0, hh - 1),
                                new Point(0, this.Height), _BarColor, darkColor);

                    e.Graphics.FillRectangle(brush, botRect);
                    brush.Dispose();
                }
            }

            //
            // Paint separators -----------------------------------------------
            //
            if (_FillStyle != FillStyles.Solid)
            {
                int sepHeight;
                int sepWidth;
                int sepHeightInc;
                int sepWidthInc;
                int targetWidth;
                Color sepColor;

                // Draw each separator line
                if (_Vertical)
                {
                    sepHeight = sepHeightInc = this.Height / (_Separators + 1);
                    for (int i = 1; i <= _Separators; i++)
                    {
                        if (sepHeight >= fillHeight)
                            sepColor = liteColor;
                        else
                            sepColor = darkColor;
                        e.Graphics.DrawLine(new Pen(sepColor, 1),
                             0, sepHeight, this.Width, sepHeight);
                        sepHeight += sepHeightInc;
                    }
                }
                else
                {
                    targetWidth = (int)((this.Width - w2) * _Target / (_Maximum + 1));
                    //                    sepWidth = sepWidthInc = (this.Width - w2) / (_Separators + 1);
                    sepWidth = sepWidthInc = targetWidth / (_Separators + 1);

                    for (int i = 1; i <= _Separators; i++)
                    {
                        if (sepWidth <= fillWidth)
                            sepColor = liteColor;
                        else
                            sepColor = darkColor;
                        e.Graphics.DrawLine(new Pen(sepColor, 1),
                        sepWidth, 0, sepWidth, this.Height);
                        sepWidth += sepWidthInc;
                    }
                    // Draw target line
                    //                   fillWidth = (int)((this.Width - w2) * _Value / _Maximum);
//                    if (targetWidth <= fillWidth)
//                        sepColor = liteColor;
//                    else
                    //                        sepColor = darkColor
                    sepColor = Color.Yellow;
                    e.Graphics.DrawLine(new Pen(sepColor, 1),
                    targetWidth, 0, targetWidth, this.Height);
                }
            }

            // draw text -------------------------------------------------------
            if (_Vertical)
            {
                if (_Target > 0)
                {
                    SolidBrush tBrush = new SolidBrush(Color.White);
                    e.Graphics.DrawString(_Target.ToString(), this.Font, tBrush, (float)10.0, (float)6.0);
                    tBrush.Dispose();
                }
                if (_Value > 0)
                {
                    SolidBrush wBrush = new SolidBrush(Color.White);
                    e.Graphics.DrawString(_Value.ToString(), this.Font, wBrush, (float)10.0, this.Height - (float)20.0);
                    wBrush.Dispose();
                }
            }
            else
            {
/*
                if (_Target > 0)
                {
                    SolidBrush tBrush = new SolidBrush(Color.White);
                    e.Graphics.DrawString(_Target.ToString(), this.Font, tBrush, (float)10.0, (float)6.0);
                    tBrush.Dispose();
                }
*/
                if (_ScaleInLB)
                {
                    if (_Value > 0)
                    {
                        SolidBrush wBrush = new SolidBrush(Color.White);
                        e.Graphics.DrawString(_Value.ToString("F00"), this.Font, wBrush, (float)10.0, this.Height - (float)20.0);
                        wBrush.Dispose();
                    }
                }
                else
                {
                    if (_Value > 0)
                    {
                        SolidBrush wBrush = new SolidBrush(Color.White);
                        e.Graphics.DrawString(_Value.ToString("F02"), this.Font, wBrush, (float)5.0, this.Height - (float)20.0);
                        wBrush.Dispose();
                    }
                    if (_Pct > 0)
                    {
                        SolidBrush bBrush = new SolidBrush(Color.Black);
                        e.Graphics.DrawString(_Pct.ToString("F00"), this.Font, bBrush, (float)58.0, this.Height - (float)20.0);
                        bBrush.Dispose();
                    }
                }
/*
                if (_Flow > 0)
                {
                    SolidBrush fBrush = new SolidBrush(Color.White);
                    e.Graphics.DrawString(_Flow.ToString(), this.Font, fBrush,
                       this.Width -w2 - (float)40.0, this.Height - (float)20.0);
                    fBrush.Dispose();
                }
 */
            }

            // Draw border and exit --------------------------------------------
            Pen pen = new Pen(_BorderColor, 3);
            Rectangle borderRect = new Rectangle(0, 0,
                ClientRectangle.Width - 1 - w2, ClientRectangle.Height - 1);

            e.Graphics.DrawRectangle(pen, borderRect);
        }
    }
}

