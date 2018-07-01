using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Navigation;


namespace primitives
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        public int PrimitivesScale = 2;

        public int FieldSize = 50;

        //public int D = 2;

        //public int sld = 20;

        Boolean SaveImages = true;
        Boolean WriteGrid = false;
        
        private Helper helper;

        public Window1()
        {
            InitializeComponent();
       
            helper = new Helper(PrimitivesScale, FieldSize, SaveImages, WriteGrid);
            helper.SetCanvas(PrimitivesCanvas);
            helper.WriteGrid();
            WritePrimitives();
            helper.ExportToPng("objects.png", 340 * PrimitivesScale, 210 * PrimitivesScale);            
        }

        public void WritePrimitives()
        {
            Object(new Point(10, 10), new Size(100, 70), "Oil terminal", Brushes.Black);
            Object(new Point(10, 100), new Size(70, 100), "Oil terminal", Brushes.Black);
            Object(new Point(120, 10), new Size(50, 50), "Forest", Brushes.ForestGreen);
            Object(new Point(180, 10), new Size(30, 30), "Forest", Brushes.ForestGreen);
            Object(new Point(90, 100), new Size(100, 100), "Mine", Brushes.DarkSlateGray);

            Object(new Point(180, 50), new Size(40, 40), "Lake", Brushes.Blue);
            RailwayStationV(new Point(200, 100), Brushes.Violet);
            RailwayStationH(new Point(230, 10), Brushes.Violet);
        }

        public void Object(Point p, Size s, string text, Brush brush)
        {
            Point _p = new Point(p.X * PrimitivesScale, p.Y * PrimitivesScale);

            PathFigure Segment = new PathFigure();
            Segment.StartPoint = new Point(_p.X, _p.Y);            
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(s.Width), _p.Y), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(s.Width), _p.Y + helper.l(s.Height)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X, _p.Y + helper.l(s.Height)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X, _p.Y), true));
            Segment.IsClosed = true;

            PathGeometry ObjectGeometry = new PathGeometry();
            ObjectGeometry.Figures.Add(Segment);
            
            Path ObjectPath = new Path();
            ObjectPath.Data = ObjectGeometry;
            ObjectPath.Fill = helper.GetHatchBrush(brush);
            ObjectPath.Stroke = brush;
            ObjectPath.StrokeThickness = 1;

            TextBlock _text = new TextBlock();
            _text.Text = text;
            _text.Background = Brushes.White;
            _text.Foreground = brush;
            _text.TextAlignment = TextAlignment.Center;
            _text.Padding = new Thickness(5, 5, 5, 5);
            _text.Measure(new Size(Double.PositiveInfinity, Double.PositiveInfinity));
            _text.Arrange(new Rect(_text.DesiredSize));
            double left = helper.l(p.X) + (helper.l(s.Width) / 2) - (_text.ActualWidth / 2);
            double top = helper.l(p.Y) + (helper.l(s.Height) / 2) - (_text.ActualHeight / 2);            
            _text.Margin = new Thickness(left, top, 0, 0);

            PrimitivesCanvas.Children.Add(ObjectPath);
            PrimitivesCanvas.Children.Add(_text);
        }

        public void RailwayStationV(Point p, Brush brush)
        {
            Size s = new Size(40, 50);

            Size platform = new Size(30, 100);

            double Yshift = (platform.Height - s.Height) / 2;

            string text = "Railway station";
            Point _p = new Point(p.X * PrimitivesScale, p.Y * PrimitivesScale);

            PathFigure Segment = new PathFigure();
            Segment.StartPoint = new Point(_p.X, _p.Y);

            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Width), _p.Y), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Width), _p.Y + helper.l(Yshift)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Width + s.Width), _p.Y + helper.l(Yshift)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Width + s.Width), _p.Y + helper.l(Yshift + s.Height)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Width), _p.Y + helper.l(Yshift + s.Height)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Width), _p.Y + helper.l(platform.Height)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X, _p.Y + helper.l(platform.Height)), true));
           
            Segment.IsClosed = true;
            Segment.IsFilled = true;

            PathGeometry ObjectGeometry = new PathGeometry();
            ObjectGeometry.Figures.Add(Segment);

            Path ObjectPath = new Path();
            ObjectPath.Data = ObjectGeometry;
            ObjectPath.Fill = helper.GetHatchBrush(brush);
            ObjectPath.Stroke = brush;
            ObjectPath.StrokeThickness = 1;           

            TextBlock _text = new TextBlock();
            _text.Text = text;
            _text.Background = Brushes.White;
            _text.Foreground = brush;
            _text.TextAlignment = TextAlignment.Center;
            _text.Padding = new Thickness(5, 5, 5, 5);
            _text.Measure(new Size(Double.PositiveInfinity, Double.PositiveInfinity));
            _text.Arrange(new Rect(_text.DesiredSize));
            double left = helper.l(p.X) + (helper.l(s.Width + platform.Width) / 2) - (_text.ActualWidth / 2);
            double top = helper.l(p.Y) + (helper.l(platform.Height) / 2) - (_text.ActualHeight / 2);
            _text.Margin = new Thickness(left, top, 0, 0);

            PrimitivesCanvas.Children.Add(ObjectPath);
            PrimitivesCanvas.Children.Add(_text);
        }
        
        public void RailwayStationH(Point p, Brush brush)
        {
            Size s = new Size(40, 50);

            Size platform = new Size(30, 100);

            double Yshift = (platform.Height - s.Height) / 2;

            string text = "Railway station";
            Point _p = new Point(p.X * PrimitivesScale, p.Y * PrimitivesScale);

            PathFigure Segment = new PathFigure();
            Segment.StartPoint = new Point(_p.X, _p.Y);

            Segment.Segments.Add(new LineSegment(new Point(_p.X, _p.Y + helper.l(platform.Width)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(Yshift), _p.Y + helper.l(platform.Width)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(Yshift), _p.Y + helper.l(platform.Width + s.Width)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(Yshift + s.Height), _p.Y + helper.l(platform.Width + s.Width)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(Yshift + s.Height), _p.Y + helper.l(platform.Width)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Height), _p.Y + helper.l(platform.Width)), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X + helper.l(platform.Height), _p.Y), true));
            Segment.Segments.Add(new LineSegment(new Point(_p.X, _p.Y), true));
            
            Segment.IsClosed = true;
            Segment.IsFilled = true;

            PathGeometry ObjectGeometry = new PathGeometry();
            ObjectGeometry.Figures.Add(Segment);

            Path ObjectPath = new Path();
            ObjectPath.Data = ObjectGeometry;
            ObjectPath.Fill = helper.GetHatchBrush(brush);
            ObjectPath.Stroke = brush;
            ObjectPath.StrokeThickness = 1;

            TextBlock _text = new TextBlock();
            _text.Text = text;
            _text.Background = Brushes.White;
            _text.Foreground = brush;
            _text.TextAlignment = TextAlignment.Center;
            _text.Padding = new Thickness(5, 5, 5, 5);
            _text.Measure(new Size(Double.PositiveInfinity, Double.PositiveInfinity));
            _text.Arrange(new Rect(_text.DesiredSize));

            double left = helper.l(p.X) + (helper.l(platform.Height) / 2) - (_text.ActualWidth / 2);
            double top = helper.l(p.Y) + (helper.l(s.Width + platform.Width) / 2) - (_text.ActualHeight / 2);

            _text.Margin = new Thickness(left, top, 0, 0);

            PrimitivesCanvas.Children.Add(ObjectPath);
            PrimitivesCanvas.Children.Add(_text);
        }
    }    
}
