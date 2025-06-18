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
[assembly: System.Runtime.InteropServices.ComVisible(false)]

namespace As
{
    [Description("ScaleCtl")]
    [ToolboxBitmap(typeof(ProgressBar))]
    [Designer(typeof(ScaleCtlDesigner))]
    public class ScaleCtl : System.Windows.Forms.Control
    {
        //
        // set default values
        //
//        private int _Separators = 0;
        private double _Topl = 0;
        private double _Maximum = 100;
        private double _Value = 0;
        private double _Target = 0;
        private double _Flow = 0;
        private bool _Open = false;
        private int _Label = 0;
        private bool _Metric = false;
        private bool _Idle = false;
        private bool _ScaleInLB = false;        //DC 3.2.0

        private Color _BarColor = Color.FromArgb(255, 128, 128);
        private Color _BorderColor = Color.Black;

        public ScaleCtl()
        {
            base.Size = new Size(20, 100);
            //            base.Font.Size = 10.0F;
            SetStyle(
                ControlStyles.AllPaintingInWmPaint |
                ControlStyles.ResizeRedraw |
                ControlStyles.DoubleBuffer,
                true
                );
        }

        [Description("ScaleCtl Open")]
        [Category("ScaleCtl")]
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

        [Description("ScaleCtl Metric")]
        [Category("ScaleCtl")]
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

        [Description("ScaleCtl ScaleInLB")]
        [Category("ScaleCtl")]
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

        [Description("ScaleCtl Label")]
        [Category("ScaleCtl")]
        public int Label
        {
            get
            {
                return _Label;
            }
            set
            {
                _Label = value;
                this.Invalidate();
            }
        }
/*
        [Description("ScaleCtl number of Separators")]
        [Category("ScaleCtl")]
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
*/
        [Description("ScaleCtl Top level")]
        [Category("ScaleCtl")]
        public double Topl
        {
            get
            {
                return _Topl;
            }
            set
            {
                _Topl = value;
                this.Invalidate();
            }
        }

        [Description("ScaleCtl color")]
        [Category("ScaleCtl")]
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

        [Description("The current value for the ScaleCtl")]
        [Category("ScaleCtl")]
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
                _Value = value;
                this.Invalidate();
            }
        }

        [Description("The uppper bound of ScaleCtl")]
        [Category("ScaleCtl")]
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

        [Description("ScaleCtl Target")]
        [Category("ScaleCtl")]
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

        [Description("ScaleCtl Flow")]
        [Category("ScaleCtl")]
        public double Flow
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

        [Description("The border color of ScaleCtl")]
        [Category("ScaleCtl")]
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
        [Description("ScaleCtl Idle")]
        [Category("ScaleCtl")]
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

        //---------------------------------------------------------------------
        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            int fillHeight = 0;
            Rectangle leftRect;
            Rectangle rightRect;
            Rectangle lowRect;
            int h1 = 18, h2;
            Color liteColor;
            Color darkColor;

            // Calculate matching colors
            if (!_Idle)
            {
                darkColor = ControlPaint.Dark(_BarColor);
                liteColor = ControlPaint.LightLight(_BarColor);
            }
            else
            {
                darkColor = liteColor = _BorderColor = _BarColor;
            }

            // The following is the height of the bar. This will vary with each value.
            h2 = this.Height - h1;
            fillHeight = (int) ((h2 * (_Maximum - _Value)) / _Maximum);

            if (fillHeight > 0)
            {
                int w1 = this.Width / 2;

                // Rectangles for left and right half of bar
                leftRect = new Rectangle(0, 0, w1, fillHeight);
                rightRect = new Rectangle(w1, 0, this.Width, fillHeight);

                // The gradient brush
                LinearGradientBrush brush;

                // Paint left half
                brush = new LinearGradientBrush(new Point(0, 0),
                            new Point(w1, 0), darkColor, _BarColor);

                e.Graphics.FillRectangle(brush, leftRect);
                brush.Dispose();

                // Paint right half
                // (this.Width/2 - 1 because there would be a dark line in the middle of the bar)
                brush = new LinearGradientBrush(new Point(w1 - 1, 0),
                          new Point(this.Width, 0), _BarColor, darkColor);

                e.Graphics.FillRectangle(brush, rightRect);
                brush.Dispose();
            }

            // Fill bottom rectangle
            SolidBrush bbrush = new SolidBrush(darkColor);
            lowRect = new Rectangle(0, fillHeight, Width, h2 - fillHeight);
            e.Graphics.FillRectangle(bbrush, lowRect);
            bbrush.Dispose();

/*
            //
            // Paint separators -----------------------------------------------
            //
            int sepHeight;
            int sepHeightInc;
            Color sepColor;

            // Draw each separator line
            sepHeight = sepHeightInc = h2 / (_Separators + 1);
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
*/
            //
            // Draw top line ---------------------------------------------
            //
            if (_Topl > 0)
            {
                int topHeight;
                Color topColor;

                // Draw top line
                topHeight = (int)(h2 * (_Maximum - _Topl) / _Maximum);

                if (topHeight >= fillHeight)
                    topColor = liteColor;
                else
                    topColor = darkColor;
                e.Graphics.DrawLine(new Pen(topColor, 1),
                     0, topHeight, this.Width, topHeight);
            }

            //
            // Draw target line -------------------------------------------
            //
           int targetHeight;
           Color targetColor;

           targetHeight = (int)(h2 * (_Maximum - _Target) / _Maximum);

            if (targetHeight >= fillHeight)
                targetColor = liteColor;
            else
                targetColor = darkColor;
            e.Graphics.DrawLine(new Pen(targetColor, 1),
                 0, targetHeight, this.Width, targetHeight);

            // draw text -------------------------------------------------------
            Color color;
            Font pFont = new Font("Arial", 18.0F, FontStyle.Bold);
            if (_Metric)
                color = Color.Yellow;
            else
                color = Color.White;
/*
            if (_Target > 0)
            {
                SolidBrush tBrush = new SolidBrush(color);
                e.Graphics.DrawString(_Target.ToString("F02"), this.Font, tBrush, (float)10.0, (float)6.0);
                tBrush.Dispose();
            }
*/
            if (_ScaleInLB)
            {
                if (_Value != 0)
                {
                    SolidBrush wBrush = new SolidBrush(color);
                    e.Graphics.DrawString(_Value.ToString("F00"), pFont, wBrush, (float)5.0, (float)(h2 - 32));
                    wBrush.Dispose();
                }

                if (_Flow != 0)
                {
                    SolidBrush fBrush = new SolidBrush(Color.Bisque);
                    e.Graphics.DrawString(_Flow.ToString("F00"), this.Font, fBrush, this.Width - (float)35.0, (float)(h2 - 22));
                    fBrush.Dispose();
                }
            }
            else
            {
                {
                    if (_Value != 0)
                    {
                        SolidBrush wBrush = new SolidBrush(color);
                        e.Graphics.DrawString(_Value.ToString("F02"), pFont, wBrush, (float)5.0, (float)(h2 - 32));
                        wBrush.Dispose();
                    }

                    if (_Flow != 0)
                    {
                        SolidBrush fBrush = new SolidBrush(Color.Bisque);
                        e.Graphics.DrawString(_Flow.ToString("F01"), this.Font, fBrush, this.Width - (float)35.0, (float)(h2 - 22));
                        fBrush.Dispose();
                    }
                }
            }
/*            
            SolidBrush vBrush = new SolidBrush(Color.White);
            switch (_Label)
            {
                case 0:
                    break;
                case 1:
                    e.Graphics.DrawString("VIBRATOR", this.Font, vBrush, this.Width - (float)80.0, (float)5.0);
                    break;
                case 2:
                    e.Graphics.DrawString("EMPTY", this.Font, vBrush, this.Width - (float)60.0, (float)5.0);
                    break;
                case 3:
                    e.Graphics.DrawString("RIGHT", this.Font, vBrush, this.Width - (float)60.0, (float)5.0);
                    break;
                case 4:
                    e.Graphics.DrawString("TILT", this.Font, vBrush, this.Width - (float)54.0, (float)5.0);
                    break;
            }
            vBrush.Dispose();
             */
            //
            // Draw border --------------------------------------------
            //
            Pen pen = new Pen(_BorderColor, 3);
            Rectangle borderRect = new Rectangle(0, 0,
                this.Width - 1, h2 - 1);

            e.Graphics.DrawRectangle(pen, borderRect);

            if (!_Open)
            {
                e.Graphics.DrawLine(pen, 2, h2, h1 + 2, this.Height);
                e.Graphics.DrawLine(pen, this.Width - 2, h2, this.Width - h1 - 2, this.Height);
                e.Graphics.DrawLine(pen, h1, this.Height - 2, this.Width - h1, this.Height - 2);
            }
            else
            {
                e.Graphics.DrawLine(pen, 2, h2, 2, this.Height);
                e.Graphics.DrawLine(pen, this.Width - 2, h2, this.Width - 2, this.Height);
                e.Graphics.DrawLine(pen, h1, this.Height - 2, this.Width - h1, this.Height - 2);
            }
        }
    }
}

