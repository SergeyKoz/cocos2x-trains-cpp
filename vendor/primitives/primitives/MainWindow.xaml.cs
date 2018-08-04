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
using System.Windows.Navigation;
using System.Windows.Shapes;
//using System.Windows.Media;

using System.IO;

namespace primitives
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public int PrimitivesScale = 2;
        public int FieldSize = 50;
        public int D = 2;
        public int sld = 20;

        Boolean SaveImages = false;
        Boolean WriteGrid = true;
        //f:\projects\trains\Platforms\cpp\MyTrains\vendor\primitives\
        public string ResourcesPath = "f:\\projects\\trains\\Platforms\\cpp\\MyTrains\\vendor\\primitives\\";

        private Helper helper;

        public MainWindow()
        {
            InitializeComponent();
            
            helper = new Helper(PrimitivesScale, FieldSize, SaveImages, WriteGrid);
            helper.SetCanvas(PrimitivesCanvas);
            helper.WriteGrid();
            WritePrimitives();
            helper.ExportToPng("rails.png", 325 * PrimitivesScale, 230 * PrimitivesScale);
            
            //UriBuilder myURI = new UriBuilder("http", "professorweb.ru", 80, "primitives.png", "#titlecode");
            //Uri uri1 = myURI.Uri;            
        }

        public void WritePrimitives()
        {
            //new
            Brush b1 = Brushes.Black;
            Brush b2 = Brushes.Red;

            double l = 36.869;
            double s1 = 14.3;
            double s2 = 30;

            WriteRailItemV_2(10, 10, D, b1);
            WriteRailItemH_2(10, 30, D, b1);

            WriteRailItem45_2(30, 20, D, b1);
            WriteRailItem135_2(30, 30, D, b1);

            CircleSection_2(10, 40, 50, 0, l, D, b1); // 1
            CircleSection_2(70, 60, 50, 90 - l, 90, D, b1); // 2
            CircleSection_2(100, 80, 50, 90, 90 + l, D, b1); // 3
            CircleSection_2(160, 40, 50, 180 - l, 180, D, b1); // 4
            CircleSection_2(180, 10, 50, 180, 180 + l, D, b1); // 5
            CircleSection_2(180, -30, 50, 270 - l, 270, D, b1); // 6
            CircleSection_2(150, -10, 50, 270, 270 + l, D, b1); // 7
            CircleSection_2(150, 10, 50, 360 - l, 360, D, b1); // 8

            CircleSection_2(210, 30, 20, 0, 90, D, b1);
            CircleSection_2(260, 30, 20, 90, 180, D, b1);
            CircleSection_2(290, 10, 20, 180, 270, D, b1);
            CircleSection_2(300, 10, 20, 270, 360, D, b1);

            WriteRailItemV_2(10, 50, D, b2);
            WriteRailItemH_2(10, 70, D, b2);

            WriteRailItem45_2(30, 60, D, b2);
            WriteRailItem135_2(30, 70, D, b2);

            CircleSection_2(10, 80, 50, 0, s1, D, b2); // 1
            CircleSection_2(10, 80, 50, l - s1, l, D, b2); // 1

            CircleSection_2(70, 100, 50, 90 - s1, 90, D, b2); // 2
            CircleSection_2(70, 100, 50, 90 - l, 90 - l + s1, D, b2); // 2


            CircleSection_2(100, 120, 50, 90, 90 + s1, D, b2); // 3
            CircleSection_2(100, 120, 50, 90 + l - s1, 90 + l, D, b2); // 3


            CircleSection_2(160, 80, 50, 180 - l, 180 - l + s1, D, b2); // 4
            CircleSection_2(160, 80, 50, 180 - s1, 180, D, b2); // 4
            
            CircleSection_2(180, 50, 50, 180, 180 + s1, D, b2); // 5
            CircleSection_2(180, 50, 50, 180 + l - s1, 180 + l, D, b2); // 5

            CircleSection_2(180, 10, 50, 270 - l, 270 - l + s1, D, b2); // 6
            CircleSection_2(180, 10, 50, 270 - s1, 270, D, b2); // 6

            CircleSection_2(150, 30, 50, 270, 270 + s1, D, b2); // 7
            CircleSection_2(150, 30, 50, 270 + l - s1, 270 + l, D, b2); // 7

            CircleSection_2(150, 50, 50, 360 - l, 360 - l + s1, D, b2); // 8
            CircleSection_2(150, 50, 50, 360 - s1, 360, D, b2); // 8

            CircleSection_2(210, 70, 20, 0, s2, D, b2);
            CircleSection_2(210, 70, 20, 90 - s2, 90, D, b2);

            CircleSection_2(260, 70, 20, 90, 90 + s2, D, b2);
            CircleSection_2(260, 70, 20, 180 - s2, 180, D, b2);

            CircleSection_2(290, 50, 20, 180, 180 + s2, D, b2);
            CircleSection_2(290, 50, 20, 270 - s2, 270, D, b2);

            CircleSection_2(300, 50, 20, 270, 270 + s2, D, b2);
            CircleSection_2(300, 50, 20, 360 - s2, 360, D, b2);

            Locomotive(10, 90, D, Brushes.Green);

            TankCar(40, 90, D, Brushes.Blue);

            Switcher(70, 90, D, Brushes.Blue);

            StartButton(10, 100, true);
            FastButton(30, 100, true);
            PauseButton(50, 100, true);
            StopButton(70, 100, true);
            BuildRailsButton(90, 100, true);
            SetSemaforesButton(110, 100, true);
            ZoomInButton(130, 100, true);
            ZoomOutButton(150, 100, true);
            UndoButton(170, 100, true);
            RedoButton(190, 100, true);
            TasksButton(210, 100, true);
            BuildRailsCheckedButton(230, 100, true);
            SetSemaforesCheckedButton(250, 100, true);

            StartButton(10, 120, false);
            FastButton(30, 120, false);
            PauseButton(50, 120, false);
            StopButton(70, 120, false);
            BuildRailsButton(90, 120, false);
            SetSemaforesButton(110, 120, false);
            ZoomInButton(130, 120, false);
            ZoomOutButton(150, 120, false);
            UndoButton(170, 120, false);
            RedoButton(190, 120, false);
            TasksButton(210, 120, false);
            BuildRailsCheckedButton(230, 120, false);
            SetSemaforesCheckedButton(250, 120, false);

            Semafor(10, 150, Colors.Green);
            Semafor(20, 150, Colors.Red);
            Semafor(30, 150, Colors.Blue);
            
            double _s1 = 37;
            double __s1 = 25;
            double _s2 = 21;

            // crossovers 1
            CircleSection_2(10, 195, 25, 90 - _s1, 90, D, b1);
            CircleSection_2(40, 155, 25, 270 - _s1, 270, D, b1);

            CircleSection_2(80, 195, 25, 90, 90 + _s1, D, b1); // 3
            CircleSection_2(50, 155, 25, 270, 270 + _s1, D, b1); // 7

            CircleSection_2(75, 180, 25, 0, _s1, D, b1); // 1
            CircleSection_2(115, 150, 25, 180, 180 + _s1, D, b1); // 5

            CircleSection_2(95, 150, 25, 360 - _s1, 360, D, b1); // 8
            CircleSection_2(135, 180, 25, 180 - _s1, 180, D, b1); // 4

            //// switches
            CircleSection_2(10, 195 + 30, 25, 90 - __s1, 90, D, b2);
            CircleSection_2(40, 155 + 30, 25, 270 - __s1, 270, D, b2);

            CircleSection_2(80, 195 + 30, 25, 90, 90 + __s1, D, b2); // 3
            CircleSection_2(50, 155 + 30, 25, 270, 270 + __s1, D, b2); // 7

            CircleSection_2(75, 180 + 40, 25, 0, __s1, D, b2); // 1
            CircleSection_2(115, 150 + 40, 25, 180, 180 + __s1, D, b2); // 5

            CircleSection_2(95, 150 + 40, 25, 360 - __s1, 360, D, b2); // 8
            CircleSection_2(135, 180 + 40, 25, 180 - __s1, 180, D, b2); // 4

            // crossovers 2
            crossover(160, 160, 31, l - _s2, l, D, b1, true); // 3
            crossover(170, 180, 31, 180 + l - _s2, 180 + l, D, b1, true); // 7

            crossover(180, 180, 31, 360 - l, 360 - l + _s2, D, b1, false); // 8
            crossover(190, 160, 31, 180 - l, 180 - l + _s2, D, b1, false); // 4

            crossover(200, 170, 31, 90 + l - _s2, 90 + l, D, b1, true); // 3
            crossover(220, 160, 31, 270 + l - _s2, 270 + l, D, b1, true); // 7

            crossover(250, 170, 31, 90 - l, 90 - l + _s2, D, b1, false); // 2
            crossover(230, 160, 31, 270 - l, 270 - l + _s2, D, b1, false); // 6

            //// switches
            crossover(150, 190, 31, l - _s2, l, D, b2, true); // 3
            crossover(170, 210, 31, 180 + l - _s2, 180 + l, D, b2, true); // 7

            crossover(180, 210, 31, 360 - l, 360 - l + _s2, D, b2, false); // 8
            crossover(200, 190, 31, 180 - l, 180 - l + _s2, D, b2, false); // 4

            crossover(210, 210, 31, 90 + l - _s2, 90 + l, D, b2, true); // 3
            crossover(230, 190, 31, 270 + l - _s2, 270 + l, D, b2, true); // 7

            crossover(260, 210, 31, 90 - l, 90 - l + _s2, D, b2, false); // 2
            crossover(240, 190, 31, 270 - l, 270 - l + _s2, D, b2, false); // 6
        }

        public void CircleSection_2(int x, int y, int r, double  a1, double  a2, int d, Brush ItemColor)
        {
            Size S;

            d = d * PrimitivesScale;
            r = r * PrimitivesScale;

            int s;

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            Point p1, p2, p3, p4;

            s = r - d;
            S = new Size(s, s);
            PathFigure Segment1 = new PathFigure();

            p1 = new Point(Math.Cos(Math.PI * a1 / 180) * (r - d) + X, -Math.Sin(Math.PI * a1 / 180) * (r - d) + Y);
            p2 = new Point(Math.Cos(Math.PI * a2 / 180) * (r - d) + X, -Math.Sin(Math.PI * a2 / 180) * (r - d) + Y);

            Segment1.StartPoint = p1;
            Segment1.Segments.Add(new ArcSegment(p2, S, 0, false, SweepDirection.Counterclockwise, true));


            s = r + d;
            S = new Size(s, s);
            PathFigure Segment2 = new PathFigure();
            p3 = new Point(Math.Cos(Math.PI * a1 / 180) * (r + d) + X, -Math.Sin(Math.PI * a1 / 180) * (r + d) + Y);
            p4 = new Point(Math.Cos(Math.PI * a2 / 180) * (r + d) + X, -Math.Sin(Math.PI * a2 / 180) * (r + d) + Y);

            Segment2.StartPoint = p3;
            Segment2.Segments.Add(new ArcSegment(p4, S, 0, false, SweepDirection.Counterclockwise, true));

            PathGeometry CilclePathGeometry = new PathGeometry();
            CilclePathGeometry.Figures.Add(Segment1);
            CilclePathGeometry.Figures.Add(Segment2);

            System.Windows.Shapes.Path CirclePath = new System.Windows.Shapes.Path();
            CirclePath.Stroke = ItemColor;
            CirclePath.StrokeThickness = 1;
            CirclePath.Data = CilclePathGeometry;

            PrimitivesCanvas.Children.Add(CirclePath);
            
            PathGeometry ClipCilclePathGeometry = new PathGeometry();

            PathFigure CilclePath = new PathFigure();
            CilclePath.StartPoint = p1;
            s = r - d;
            S = new Size(s, s);
            CilclePath.Segments.Add(new ArcSegment(p2, S, 0, false, SweepDirection.Counterclockwise, true));
            CilclePath.Segments.Add(new LineSegment(p4, false));

            s = r + d;
            S = new Size(s, s);
            CilclePath.Segments.Add(new ArcSegment(p3, S, 0, false, SweepDirection.Clockwise, true));
            ClipCilclePathGeometry.Figures.Add(CilclePath);

            double angle;
            Line LineItem;

            double a = 360 / (2 * Math.PI * (r / PrimitivesScale) * 10 / sld);

            //angle = Math.Ceiling((a1 - a / 2) / a) * a + a / 2;

            angle =  a1 + a / 2;

            double x1, y1;

            while (angle < a2)
            {
                x1 = Math.Cos(Math.PI * angle / 180) * r + x;
                y1 = -Math.Sin(Math.PI * angle / 180) * r + y;

                LineItem = helper.CreateLine(x, y, x1, y1, ItemColor, 0.5);
                LineItem.Clip = ClipCilclePathGeometry;
                PrimitivesCanvas.Children.Add(LineItem);

                angle += a;
            }
        }

        public void WriteRailItem45_2(int x, int y, double d, Brush ItemColor)
        {
            //double sld = 20;
            double sldt = sld / Math.Sqrt(2) / 10;            
            double dt = d * Math.Sqrt(2) / 2;
            double i = 0.5;
            double l = i * sldt;

            while (l < 10)
            {
                PrimitivesCanvas.Children.Add(helper.CreateLine(x - dt + l, y - dt - l, x + dt + l, y + dt - l, ItemColor, 0.5));
                l = i * sldt;
                i++;
            }

            PrimitivesCanvas.Children.Add(helper.CreateLine(x - dt, y - dt, x + 10 - dt, y - 10 - dt, ItemColor, 1));
            PrimitivesCanvas.Children.Add(helper.CreateLine(x + dt, y + dt, x + 10 + dt, y - 10 + dt, ItemColor, 1));
        }

        public void WriteRailItem135_2(int x, int y, double d, Brush ItemColor)
        {
            //double sld = 20;
            double sldt = sld / Math.Sqrt(2) / 10;
            double dt = d * Math.Sqrt(2) / 2;
            double i = 0.5;
            double l = i * sldt;

            while (l < 10)
            {
                PrimitivesCanvas.Children.Add(helper.CreateLine(x - dt + l, y + dt + l, x + dt + l, y - dt + l, ItemColor, 0.5));
                l = i * sldt;
                i++;
            }

            PrimitivesCanvas.Children.Add(helper.CreateLine(x + dt, y - dt, x + 10 + dt, y + 10 - dt, ItemColor, 1));
            PrimitivesCanvas.Children.Add(helper.CreateLine(x - dt, y + dt, x + 10 - dt, y + 10 + dt, ItemColor, 1));
        }

        public void WriteRailItemH_2(int x, int y, double d, Brush ItemColor)
        {
            double sldt = sld / 10;      
            double i = 0.5;
            double l = i * sldt;

            while (l < 10)
            {
                PrimitivesCanvas.Children.Add(helper.CreateLine(x + l, y + d, x + l, y - d, ItemColor, 0.3));
                l = i * sldt;
                i++;
            }

            PrimitivesCanvas.Children.Add(helper.CreateLine(x, y - d, x + 10, y - d, ItemColor, 1));
            PrimitivesCanvas.Children.Add(helper.CreateLine(x, y + d, x + 10, y + d, ItemColor, 1));
        }

        public void WriteRailItemV_2(int x, int y, double d, Brush ItemColor)
        {
            double sldt = sld / 10;
            double i = 0.5;
            double l = i * sldt;

            while (l < 10)
            {
                PrimitivesCanvas.Children.Add(helper.CreateLine(x + d, y + l, x - d, y + l, ItemColor, 0.3));
                l = i * sldt;
                i++;
            }

            PrimitivesCanvas.Children.Add(helper.CreateLine(x - d, y, x - d, y + 10, ItemColor, 1));
            PrimitivesCanvas.Children.Add(helper.CreateLine(x + d, y, x + d, y + 10, ItemColor, 1));
        }

        public void Locomotive(int x, int y, int d, Brush ItemColor)
        {
            
            d = d * PrimitivesScale;
           
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PathFigure Segment2 = new PathFigure();

            Segment2.StartPoint = new Point(X + l(0.5), Y);
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y - l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(14), Y - l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(18.5), Y - l(1.25)), true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(18.5), Y + l(1.25)), new Size(l(8), l(2.5)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(14), Y + l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y), true));

            Segment2.IsFilled = true;

            PathGeometry CarGeometry1 = new PathGeometry();
           
            CarGeometry1.Figures.Add(Segment2);
        

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = ItemColor;
            CarPath1.StrokeThickness = 1;

            CarPath1.Fill = Brushes.White;
            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);

            PathFigure Segment1 = new PathFigure();

            Segment1.StartPoint = new Point(X + l(14), Y - l(1.5));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(16), Y - l(1)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(16), Y + l(1)), new Size(l(9), l(3)), 0, false, SweepDirection.Clockwise, true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(14), Y + l(1.5)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(14), Y - l(1.5)), new Size(l(4), l(3)), 0, false, SweepDirection.Counterclockwise, true));
            Segment1.IsFilled = true;

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X, Y - l(0.25));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(0.5), Y - l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X, Y + l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X, Y - l(0.25)), true));

            PathFigure Segment4 = new PathFigure();
            Segment4.StartPoint = new Point(X + l(19.5), Y - l(0.25));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19.5), Y - l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19.5), Y + l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(20), Y + l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(20), Y - l(0.25)), true));
            Segment4.IsFilled = true;
            
            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment1);
            //CarGeometry2.Figures.Add(Segment2);
            CarGeometry2.Figures.Add(Segment3);
            CarGeometry2.Figures.Add(Segment4);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = ItemColor;
            CarPath2.StrokeThickness = 1;

            CarPath2.Fill = ItemColor;
            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void TankCar(int x, int y, int d, Brush ItemColor)
        {
            d = d * PrimitivesScale;

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(2), Y - l(2.5));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(18), Y - l(2.5)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(18), Y + l(2.5)), new Size(l(10), l(5)), 0, false, SweepDirection.Clockwise, true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(2), Y + l(2.5)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(2), Y - l(2.5)), new Size(l(10), l(5)), 0, false, SweepDirection.Clockwise, true));
            Segment1.IsFilled = true;

            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);
          
            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = ItemColor;
            CarPath1.StrokeThickness = 0.5;

            CarPath1.Fill = Brushes.White;

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);
            
            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(9), Y);
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(11), Y), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(9), Y), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));          
            Segment2.IsFilled = false;

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X, Y - l(0.25));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(0.5), Y - l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X, Y + l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X, Y - l(0.25)), true));
            Segment3.IsFilled = true;

            PathFigure Segment4 = new PathFigure();
            Segment4.StartPoint = new Point(X + l(19.5), Y - l(0.25));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19.5), Y - l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19.5), Y + l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(20), Y + l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(20), Y - l(0.25)), true));
            Segment4.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();            
            CarGeometry2.Figures.Add(Segment2);
            CarGeometry2.Figures.Add(Segment3);
            CarGeometry2.Figures.Add(Segment4);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = ItemColor;
            CarPath2.StrokeThickness = 0.5;

            CarPath2.Fill = ItemColor;
           
            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void Switcher(int x, int y, int d, Brush ItemColor)
        {
            d = d * PrimitivesScale;

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(0.5), Y - l(2.5));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(15.5), Y - l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(15.5), Y + l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y - l(2.5)), true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = ItemColor;
            CarPath1.StrokeThickness = 0.5;

            CarPath1.Fill = Brushes.White;

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);
           
            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(3), Y - l(2.5));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(7), Y - l(2.5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(2.5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(2.5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(3), Y - l(2.5)), true));
            Segment1.IsFilled = true;
       
            /*PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(0.5), Y - l(2.5));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(15.5), Y - l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(15.5), Y + l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(2.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y - l(2.5)), true));
            Segment2.IsFilled = false;*/
            
            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X, Y - l(0.25));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(0.5), Y - l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X, Y + l(0.25)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X, Y - l(0.25)), true));
            Segment3.IsFilled = true;
            
            PathFigure Segment4 = new PathFigure();
            Segment4.StartPoint = new Point(X + l(15.5), Y - l(0.25));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(15.5), Y - l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(15.5), Y + l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(16), Y + l(0.25)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(16), Y - l(0.25)), true));
            Segment4.IsFilled = true;
            
            PathFigure Segment5 = new PathFigure();
            Segment5.StartPoint = new Point(X + l(1), Y - l(1.5));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(3), Y - l(1.5)), true));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(1.5)), true));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(1), Y + l(1.5)), true));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(1), Y - l(1.5)), true));
            Segment5.IsFilled = false;

            PathFigure Segment6 = new PathFigure();
            Segment6.StartPoint = new Point(X + l(7), Y - l(1.5));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(15), Y - l(1.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(1.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(1.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(7), Y - l(1.5)), true));
            Segment6.IsFilled = false;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment1);
            //CarGeometry2.Figures.Add(Segment2);
            CarGeometry2.Figures.Add(Segment3);
            CarGeometry2.Figures.Add(Segment4);
            CarGeometry2.Figures.Add(Segment5);
            CarGeometry2.Figures.Add(Segment6);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = ItemColor;
            CarPath2.StrokeThickness = 0.5;

            CarPath2.Fill = ItemColor;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public double l(double l)
        {
            return l * PrimitivesScale;
        }

        public System.Windows.Shapes.Path BorderButton(int x, int y)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PathFigure SegmentBorder = new PathFigure();
            SegmentBorder.StartPoint = new Point(X, Y);
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(20), Y), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(20), Y + l(20)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X, Y + l(20)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X, Y), true));

            SegmentBorder.IsFilled = true;

            PathGeometry GeometryBorder = new PathGeometry();
            GeometryBorder.Figures.Add(SegmentBorder);

            System.Windows.Shapes.Path BorderPath = new System.Windows.Shapes.Path();
            BorderPath.Stroke = Brushes.White;
            BorderPath.StrokeThickness = 0.5;

            BorderPath.Fill = Brushes.White;

            BorderPath.Data = GeometryBorder;

            return BorderPath;
        }

        public void StartButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(6.5), Y + l(4));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(10)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(6.5), Y + l(16)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(6.5), Y + l(5)), true));            
            Segment1.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment1);
            
            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void FastButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(1.5), Y + l(4));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(10), Y + l(10)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1.5), Y + l(16)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1.5), Y + l(5)), true));
            Segment1.IsFilled = true;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(10), Y + l(4));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(18.5), Y + l(10)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(10), Y + l(16)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(10), Y + l(5)), true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment1);
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void PauseButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(5), Y + l(5));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(8.5), Y + l(5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(8.5), Y + l(15)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(15)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(5)), true));
            Segment1.IsFilled = true;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(11.5), Y + l(5));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(15)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(11.5), Y + l(15)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(11.5), Y + l(5)), true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment1);
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void StopButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(5), Y + l(5));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(15)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(15)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(5)), true));
            Segment1.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment1);
           
            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void BuildRailsButton(int x, int y, Boolean Enable)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            double d = l(2);

            double dt = d * Math.Sqrt(2) / 2;
           

            double dc = l(4);

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + dc, Y + l(20) - dc);
            Segment1.Segments.Add(new LineSegment(new Point(X + l(20) - dc, Y + dc), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(20) - dc, Y + dc), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + dc, Y + l(20) - dc), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + dc, Y + l(20) - dc), true));
            Segment1.IsFilled = true;

            double x1, y1, x2, y2;

            double dw;

            dw = l(0.15);

            x1 = X + dc - dt; 
            y1 = Y + l(20) - dc - dt;

            x2 = X + l(20) - dc - dt;
            y2 = Y + dc - dt;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(x1 - dw, y1 - dw);
            Segment2.Segments.Add(new LineSegment(new Point(x2 - dw, y2 - dw), true));
            Segment2.Segments.Add(new LineSegment(new Point(x2 + dw, y2 + dw), true));
            Segment2.Segments.Add(new LineSegment(new Point(x1 + dw, y1 + dw), true));
            Segment2.Segments.Add(new LineSegment(new Point(x1 - dw, y1 - dw), true));
            Segment2.IsFilled = true;

            x1 = X + dc + dt;
            y1 = Y + l(20) - dc + dt;

            x2 = X + l(20) - dc + dt;
            y2 = Y + dc + dt;

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(x1 - dw, y1 - dw);
            Segment3.Segments.Add(new LineSegment(new Point(x2 - dw, y2 - dw), true));
            Segment3.Segments.Add(new LineSegment(new Point(x2 + dw, y2 + dw), true));
            Segment3.Segments.Add(new LineSegment(new Point(x1 + dw, y1 + dw), true));
            Segment3.Segments.Add(new LineSegment(new Point(x1 - dw, y1 - dw), true));
            Segment3.IsFilled = true;
           
            PathGeometry CarGeometry2 = new PathGeometry();
            //CarGeometry2.Figures.Add(Segment1);
            CarGeometry2.Figures.Add(Segment2);
            CarGeometry2.Figures.Add(Segment3);

            PathFigure SlepperSegment;

            /*
             
           double sldt = sld / Math.Sqrt(2) / 10;
            
           double i = 0.5;
           double ll = i * sldt;

           while (ll < 10)
           {
               PrimitivesCanvas.Children.Add(CreateLine(x - dt + ll, y - dt - ll, x + dt + ll, y + dt - ll, ItemColor, 0.5));
               ll = i * sldt;
               i++;
           }*/

            double sld = l(24);
            double sldt = sld / Math.Sqrt(2) / 10;
            double i = 0.5;
            double ll = i * sldt;
            double dt_sl = dt + l(1);

            dw = l(0.3);

            while (ll < l(12))
            {
                x1 = X + dc - dt_sl + ll;
                y1 = Y - dc + l(20) - dt_sl - ll;

                x2 = X + dc + dt_sl + ll;
                y2 = Y - dc + l(20) + dt_sl - ll;

                SlepperSegment = new PathFigure();
                SlepperSegment.StartPoint = new Point(x1 + dw, y1 - dw);
                SlepperSegment.Segments.Add(new LineSegment(new Point(x2 + dw, y2 - dw), true));
                SlepperSegment.Segments.Add(new LineSegment(new Point(x2 - dw, y2 + dw), true));
                SlepperSegment.Segments.Add(new LineSegment(new Point(x1 - dw, y1 + dw), true));
                SlepperSegment.Segments.Add(new LineSegment(new Point(x1 + dw, y1 - dw), true));
                SlepperSegment.IsFilled = false;
                
                i++;

                ll = i * sldt;

                CarGeometry2.Figures.Add(SlepperSegment);
            }

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void SetSemaforesButton(int x, int y, Boolean Enable)
        {
           
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(15), Y + l(7));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(13)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(5), Y + l(13)), new Size(l(2), l(2)), 0, false, SweepDirection.Clockwise, true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(7)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(15), Y + l(7)), new Size(l(2), l(2)), 0, false, SweepDirection.Clockwise, true));
            Segment1.IsFilled = true;
        

            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = Brushes.Black;
            CarPath1.StrokeThickness = 0.5;

            CarPath1.Fill = Brushes.Black;

            if (!Enable) { 
                CarPath1.Opacity = 0.5;
            }

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(8), Y + l(7));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(7)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(8), Y + l(7)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.IsFilled = true;
                        
            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Red;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X + l(8), Y + l(13));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(13)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(8), Y + l(13)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.IsFilled = true;

            PathGeometry CarGeometry3 = new PathGeometry();
            CarGeometry3.Figures.Add(Segment3);         

            System.Windows.Shapes.Path CarPath3 = new System.Windows.Shapes.Path();
            CarPath3.Stroke = Brushes.Black;
            CarPath3.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath3.Opacity = 0.5;
            }

            CarPath3.Fill = Brushes.Green;

            CarPath3.Data = CarGeometry3;

            PrimitivesCanvas.Children.Add(CarPath3);
        }

        public void ZoomInButton(int x, int y, Boolean Enable)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(5), Y + l(8));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(17), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(5), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);            

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X + l(6), Y + l(8));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(16), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(6), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.IsFilled = true;

            PathGeometry CarGeometry3 = new PathGeometry();
            CarGeometry3.Figures.Add(Segment3);

            System.Windows.Shapes.Path CarPath3 = new System.Windows.Shapes.Path();
            CarPath3.Stroke = Brushes.Black;
            CarPath3.StrokeThickness = 0.5;

            CarPath3.Fill = Brushes.White;

            CarPath3.Data = CarGeometry3;

            PrimitivesCanvas.Children.Add(CarPath3);

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(1), Y + l(16));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(6), Y + l(11)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(8), Y + l(13)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(18)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1), Y + l(16)), true));
            Segment1.IsFilled = true;

            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = Brushes.Black;
            CarPath1.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath1.Opacity = 0.5;
            }

            CarPath1.Fill = Brushes.Black;

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);


            PathFigure Segment4 = new PathFigure();
            Segment4.StartPoint = new Point(X + l(13), Y + l(15));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(15)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(13)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(17), Y + l(13)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(17), Y + l(15)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19), Y + l(15)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(17), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(17), Y + l(19)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(19)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(13), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(13), Y + l(15)), true));
            Segment4.IsFilled = true;

            PathGeometry CarGeometry4 = new PathGeometry();
            CarGeometry4.Figures.Add(Segment4);

            System.Windows.Shapes.Path CarPath4 = new System.Windows.Shapes.Path();
            CarPath4.Stroke = Brushes.Black;
            CarPath4.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath4.Opacity = 0.5;
            }

            CarPath4.Fill = Brushes.Black;

            CarPath4.Data = CarGeometry4;

            PrimitivesCanvas.Children.Add(CarPath4);
        }

        public void ZoomOutButton(int x, int y, Boolean Enable)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(5), Y + l(8));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(17), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(5), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }


            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X + l(6), Y + l(8));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(16), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(6), Y + l(8)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.IsFilled = true;


            PathGeometry CarGeometry3 = new PathGeometry();
            CarGeometry3.Figures.Add(Segment3);

            System.Windows.Shapes.Path CarPath3 = new System.Windows.Shapes.Path();
            CarPath3.Stroke = Brushes.Black;
            CarPath3.StrokeThickness = 0.5;

            CarPath3.Fill = Brushes.White;

            CarPath3.Data = CarGeometry3;

            PrimitivesCanvas.Children.Add(CarPath3);

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(1), Y + l(16));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(6), Y + l(11)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(8), Y + l(13)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(18)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1), Y + l(16)), true));
            Segment1.IsFilled = true;

            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = Brushes.Black;
            CarPath1.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath1.Opacity = 0.5;
            }

            CarPath1.Fill = Brushes.Black;

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);

            PathFigure Segment4 = new PathFigure();
            Segment4.StartPoint = new Point(X + l(13), Y + l(15));           
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19), Y + l(15)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(19), Y + l(17)), true));            
            Segment4.Segments.Add(new LineSegment(new Point(X + l(13), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(13), Y + l(15)), true));
            Segment4.IsFilled = true;

            PathGeometry CarGeometry4 = new PathGeometry();
            CarGeometry4.Figures.Add(Segment4);

            System.Windows.Shapes.Path CarPath4 = new System.Windows.Shapes.Path();
            CarPath4.Stroke = Brushes.Black;
            CarPath4.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath4.Opacity = 0.5;
            }

            CarPath4.Fill = Brushes.Black;

            CarPath4.Data = CarGeometry4;

            PrimitivesCanvas.Children.Add(CarPath4);
        }

        public void UndoButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(12), Y + l(6));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(14)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(12), Y + l(16)), true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(4)), new Size(l(1), l(1)), 0, false, SweepDirection.Counterclockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(3), Y + l(10)), new Size(l(12), l(12)), 0, false, SweepDirection.Counterclockwise, true));

            Segment2.Segments.Add(new LineSegment(new Point(X + l(1.3), Y + l(9)), true));

            Segment2.Segments.Add(new LineSegment(new Point(X + l(2.15), Y + l(13.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(6.15), Y + l(12.25)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(11.15)), true));
            
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(6)), new Size(l(12), l(12)), 0, false, SweepDirection.Clockwise, true));

            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }


            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void RedoButton(int x, int y, Boolean Enable)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(20 - 12), Y + l(6));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(20 - 12), Y + l(14)), new Size(l(1), l(1)), 0, false, SweepDirection.Counterclockwise, true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(20 - 12), Y + l(16)), true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(20 - 12), Y + l(4)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(20 - 3), Y + l(10)), new Size(l(12), l(12)), 0, false, SweepDirection.Clockwise, true));

            Segment2.Segments.Add(new LineSegment(new Point(X + l(20 - 1.3), Y + l(9)), true));

            Segment2.Segments.Add(new LineSegment(new Point(X + l(20 - 2.15), Y + l(13.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(20 - 6.15), Y + l(12.25)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(20 - 4.5), Y + l(11.15)), true));

            Segment2.Segments.Add(new ArcSegment(new Point(X + l(20 - 12), Y + l(6)), new Size(l(12), l(12)), 0, false, SweepDirection.Counterclockwise, true));

            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }


            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }

        public void TasksButton(int x, int y, Boolean Enable)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(7), Y + l(3));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(3)), true)); 
            Segment1.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(5)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(3)), true));
            Segment1.IsFilled = true;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(7), Y + l(7));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(7)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(9)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(9)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(7)), true));
            Segment2.IsFilled = true;

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X + l(7), Y + l(11));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(11)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(13)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(13)), true));
            Segment3.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(11)), true));
            Segment3.IsFilled = true;

            PathFigure Segment4 = new PathFigure();
            Segment4.StartPoint = new Point(X + l(7), Y + l(15));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(15)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(17)), true));
            Segment4.Segments.Add(new LineSegment(new Point(X + l(7), Y + l(15)), true));
            Segment4.IsFilled = true;

            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);
            CarGeometry1.Figures.Add(Segment2);
            CarGeometry1.Figures.Add(Segment3);
            CarGeometry1.Figures.Add(Segment4);
            
            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = Brushes.Black;
            CarPath1.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath1.Opacity = 0.5;
            }


            CarPath1.Fill = Brushes.Black;

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);

            PathFigure Segment5 = new PathFigure();
            Segment5.StartPoint = new Point(X + l(2.5), Y + l(2.5));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(4)), true));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(5.5), Y + l(3)), true));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(5.5)), true));
            Segment5.Segments.Add(new LineSegment(new Point(X + l(2.5), Y + l(2.5)), true));
            Segment5.IsFilled = true;

            PathFigure Segment55 = new PathFigure();
            Segment55.StartPoint = new Point(X + l(2.5), Y + l(6.5));
            Segment55.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(8)), true));
            Segment55.Segments.Add(new LineSegment(new Point(X + l(5.5), Y + l(7)), true));
            Segment55.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(9.5)), true));
            Segment55.Segments.Add(new LineSegment(new Point(X + l(2.5), Y + l(6.5)), true));
            Segment55.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment5);
            CarGeometry2.Figures.Add(Segment55);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Green;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }


            CarPath2.Fill = Brushes.Green;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);




            PathFigure Segment6 = new PathFigure();
            Segment6.StartPoint = new Point(X + l(3.5), Y + l(12));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(11.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(3.5), Y + l(11)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(11.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(11)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(11.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(12)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(12.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(13)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(12.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(3.5), Y + l(13)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(12.5)), true));
            Segment6.Segments.Add(new LineSegment(new Point(X + l(3.5), Y + l(12)), true));
            
            Segment6.IsFilled = true;

            PathFigure Segment7 = new PathFigure();
            Segment7.StartPoint = new Point(X + l(3.5), Y + l(16));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(15.5)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(3.5), Y + l(15)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(15.5)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(15)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(15.5)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(16)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(16.5)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(4.5), Y + l(17)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(4), Y + l(16.5)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(3.5), Y + l(17)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(3), Y + l(16.5)), true));
            Segment7.Segments.Add(new LineSegment(new Point(X + l(3.5), Y + l(16)), true));
            Segment7.IsFilled = true;

            PathGeometry CarGeometry3 = new PathGeometry();
            CarGeometry3.Figures.Add(Segment6);
            CarGeometry3.Figures.Add(Segment7);

            System.Windows.Shapes.Path CarPath3 = new System.Windows.Shapes.Path();
            CarPath3.Stroke = Brushes.Red;
            CarPath3.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath3.Opacity = 0.5;
            }

            CarPath3.Fill = Brushes.Red;

            CarPath3.Data = CarGeometry3;

            PrimitivesCanvas.Children.Add(CarPath3);

        }
        
        public void BuildRailsCheckedButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));

            PrimitivesCanvas.Children.Add(CheckedBorderButton(x, y, Enable));

            double d = l(2);
            double dt = d * Math.Sqrt(2) / 2;
            double dc = l(4);

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + dc, Y + l(20) - dc);
            Segment1.Segments.Add(new LineSegment(new Point(X + l(20) - dc, Y + dc), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(20) - dc, Y + dc), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + dc, Y + l(20) - dc), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + dc, Y + l(20) - dc), true));
            Segment1.IsFilled = true;

            double x1, y1, x2, y2;

            double dw;

            dw = l(0.15);

            x1 = X + dc - dt;
            y1 = Y + l(20) - dc - dt;

            x2 = X + l(20) - dc - dt;
            y2 = Y + dc - dt;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(x1 - dw, y1 - dw);
            Segment2.Segments.Add(new LineSegment(new Point(x2 - dw, y2 - dw), true));
            Segment2.Segments.Add(new LineSegment(new Point(x2 + dw, y2 + dw), true));
            Segment2.Segments.Add(new LineSegment(new Point(x1 + dw, y1 + dw), true));
            Segment2.Segments.Add(new LineSegment(new Point(x1 - dw, y1 - dw), true));
            Segment2.IsFilled = true;

            x1 = X + dc + dt;
            y1 = Y + l(20) - dc + dt;

            x2 = X + l(20) - dc + dt;
            y2 = Y + dc + dt;

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(x1 - dw, y1 - dw);
            Segment3.Segments.Add(new LineSegment(new Point(x2 - dw, y2 - dw), true));
            Segment3.Segments.Add(new LineSegment(new Point(x2 + dw, y2 + dw), true));
            Segment3.Segments.Add(new LineSegment(new Point(x1 + dw, y1 + dw), true));
            Segment3.Segments.Add(new LineSegment(new Point(x1 - dw, y1 - dw), true));
            Segment3.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();            
            CarGeometry2.Figures.Add(Segment2);
            CarGeometry2.Figures.Add(Segment3);

            PathFigure SlepperSegment;

            double sld = l(24);
            double sldt = sld / Math.Sqrt(2) / 10;
            double i = 0.5;
            double ll = i * sldt;
            double dt_sl = dt + l(1);

            dw = l(0.3);

            while (ll < l(12))
            {
                x1 = X + dc - dt_sl + ll;
                y1 = Y - dc + l(20) - dt_sl - ll;

                x2 = X + dc + dt_sl + ll;
                y2 = Y - dc + l(20) + dt_sl - ll;

                SlepperSegment = new PathFigure();
                SlepperSegment.StartPoint = new Point(x1 + dw, y1 - dw);
                SlepperSegment.Segments.Add(new LineSegment(new Point(x2 + dw, y2 - dw), true));
                SlepperSegment.Segments.Add(new LineSegment(new Point(x2 - dw, y2 + dw), true));
                SlepperSegment.Segments.Add(new LineSegment(new Point(x1 - dw, y1 + dw), true));
                SlepperSegment.Segments.Add(new LineSegment(new Point(x1 + dw, y1 - dw), true));
                SlepperSegment.IsFilled = false;

                i++;

                ll = i * sldt;

                CarGeometry2.Figures.Add(SlepperSegment);
            }

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;

            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Black;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);
        }
        
        public void SetSemaforesCheckedButton(int x, int y, Boolean Enable)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PrimitivesCanvas.Children.Add(BorderButton(x, y));
            PrimitivesCanvas.Children.Add(CheckedBorderButton(x, y, Enable));

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(15), Y + l(7));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(15), Y + l(13)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(5), Y + l(13)), new Size(l(2), l(2)), 0, false, SweepDirection.Clockwise, true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(5), Y + l(7)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(15), Y + l(7)), new Size(l(2), l(2)), 0, false, SweepDirection.Clockwise, true));
            Segment1.IsFilled = true;


            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = Brushes.Black;
            CarPath1.StrokeThickness = 0.5;

            CarPath1.Fill = Brushes.Black;

            if (!Enable)
            {
                CarPath1.Opacity = 0.5;
            }

            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(8), Y + l(7));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(7)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.Segments.Add(new ArcSegment(new Point(X + l(8), Y + l(7)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();
            CarPath2.Stroke = Brushes.Black;
            CarPath2.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath2.Opacity = 0.5;
            }

            CarPath2.Fill = Brushes.Red;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);

            PathFigure Segment3 = new PathFigure();
            Segment3.StartPoint = new Point(X + l(8), Y + l(13));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(12), Y + l(13)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.Segments.Add(new ArcSegment(new Point(X + l(8), Y + l(13)), new Size(l(1), l(1)), 0, false, SweepDirection.Clockwise, true));
            Segment3.IsFilled = true;

            PathGeometry CarGeometry3 = new PathGeometry();
            CarGeometry3.Figures.Add(Segment3);

            System.Windows.Shapes.Path CarPath3 = new System.Windows.Shapes.Path();
            CarPath3.Stroke = Brushes.Black;
            CarPath3.StrokeThickness = 0.5;
            if (!Enable)
            {
                CarPath3.Opacity = 0.5;
            }

            CarPath3.Fill = Brushes.Green;

            CarPath3.Data = CarGeometry3;

            PrimitivesCanvas.Children.Add(CarPath3);
        }
        
        public System.Windows.Shapes.Path CheckedBorderButton(int x, int y, Boolean Enable)
        {
            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PathFigure SegmentBorder = new PathFigure();
            SegmentBorder.StartPoint = new Point(X, Y);
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(20), Y), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(20), Y + l(20)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X, Y + l(20)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X, Y + l(2)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(2), Y + l(2)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(2), Y + l(18)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(18)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X + l(18), Y + l(2)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X, Y + l(2)), true));
            SegmentBorder.Segments.Add(new LineSegment(new Point(X, Y), true));

            SegmentBorder.IsFilled = true;

            PathGeometry GeometryBorder = new PathGeometry();
            GeometryBorder.Figures.Add(SegmentBorder);

            System.Windows.Shapes.Path BorderPath = new System.Windows.Shapes.Path();
            BorderPath.Stroke = Brushes.Black;
            BorderPath.StrokeThickness = 0.5;

            if (!Enable)
            {
                BorderPath.Opacity = 0.5;
            }

            BorderPath.Fill = Brushes.Black;

            BorderPath.Data = GeometryBorder;

            return BorderPath;
        }


        public void Semafor(int x, int y, Color ItemColor)
        {

            float X = x * PrimitivesScale;
            float Y = y * PrimitivesScale;

            PathFigure Segment2 = new PathFigure();
            Segment2.StartPoint = new Point(X + l(0.5), Y);
            Segment2.Segments.Add(new LineSegment(new Point(X + l(6), Y + l(1.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(6), Y + l(-1.5)), true));
            Segment2.Segments.Add(new LineSegment(new Point(X + l(0.5), Y), true));
            Segment2.IsFilled = true;

            PathGeometry CarGeometry2 = new PathGeometry();
            CarGeometry2.Figures.Add(Segment2);

            System.Windows.Shapes.Path CarPath2 = new System.Windows.Shapes.Path();

            LinearGradientBrush GradientBrushSemafor = new LinearGradientBrush(ItemColor, Colors.White, new Point(0, 0), new Point(1.5, 0));
            
            CarPath2.Stroke = GradientBrushSemafor;
            CarPath2.StrokeThickness = 0.5;

            CarPath2.Fill = GradientBrushSemafor;

            CarPath2.Data = CarGeometry2;

            PrimitivesCanvas.Children.Add(CarPath2);

            /*PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X, Y + l(2));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(2)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(0.5)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(0.5), Y + l(-0.5)), new Size(l(0.5), l(0.5)), 0, false, SweepDirection.Counterclockwise, true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(0.5), Y + l(-2)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X, Y + l(-2)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X, Y + l(2)), true));
            Segment1.IsFilled = true;*/

            PathFigure Segment1 = new PathFigure();
            Segment1.StartPoint = new Point(X + l(1.5), Y + l(2));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1), Y + l(2)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1), Y + l(0.5)), true));
            Segment1.Segments.Add(new ArcSegment(new Point(X + l(1), Y + l(-0.5)), new Size(l(0.5), l(0.5)), 0, false, SweepDirection.Clockwise, true));
            Segment1.Segments.Add(new LineSegment(new Point(X + l(1), Y + l(-2)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X+ l(1.5), Y + l(-2)), true));
            Segment1.Segments.Add(new LineSegment(new Point(X+ l(1.5), Y + l(2)), true));
            Segment1.IsFilled = true;
            
            PathGeometry CarGeometry1 = new PathGeometry();
            CarGeometry1.Figures.Add(Segment1);

            System.Windows.Shapes.Path CarPath1 = new System.Windows.Shapes.Path();
            CarPath1.Stroke = Brushes.Black;
            CarPath1.StrokeThickness = 0.5;

            CarPath1.Fill = Brushes.Black;
           
            CarPath1.Data = CarGeometry1;

            PrimitivesCanvas.Children.Add(CarPath1);
        }
        
        public void crossover(double x, double y, double r, double a1, double a2, double d, Brush ItemColor, bool f)
        {
            //Console.WriteLine("x = " + x + ";  y=" + y);
            //crossover(10, 220, 
            //r = 50, 
            //a1 = 90 - s1, 
            //a2 = 90, 
            //D, b2); // 2

            //crossover(10, 220, 
            //r = 50, 
            //90 - l, 
            //90 - l + s1, 
            //D, b2); // 3
            /*double l = 36.869;
            double s1 = 14.3;
            double s2 = 30;

            public int PrimitivesScale = 2;
            public int FieldSize = 50;
            public int D = 2;
            public int sld = 20;             
             */

            Size S;

            d = d * PrimitivesScale;
            r = r * PrimitivesScale;

            double s;

            double _x, _y;

            if (f)
            {
                _x = (x * PrimitivesScale) - Math.Cos(Math.PI * a2 / 180) * r;
                _y = (y * PrimitivesScale) + Math.Sin(Math.PI * a2 / 180) * r;
            }
            else
            {
                _x = (x * PrimitivesScale) - Math.Cos(Math.PI * a1 / 180) * r;
                _y = (y * PrimitivesScale) + Math.Sin(Math.PI * a1 / 180) * r;
            }

            x = _x / PrimitivesScale;
            y = _y / PrimitivesScale;
  
            double X = x * PrimitivesScale;
            double Y = y * PrimitivesScale;


            Point p1, p2, p3, p4;
            //inner r
            s = r - d;
            S = new Size(s, s);
            PathFigure Segment1 = new PathFigure();
            
            p1 = new Point(Math.Cos(Math.PI * a1 / 180) * (r - d) + X, -Math.Sin(Math.PI * a1 / 180) * (r - d) + Y);
            p2 = new Point(Math.Cos(Math.PI * a2 / 180) * (r - d) + X, -Math.Sin(Math.PI * a2 / 180) * (r - d) + Y);
            
            Segment1.StartPoint = p1;
            Segment1.Segments.Add(new ArcSegment(p2, S, 0, false, SweepDirection.Counterclockwise, true));

            //outer r
            s = r + d;
            S = new Size(s, s);
            PathFigure Segment2 = new PathFigure();
            p3 = new Point(Math.Cos(Math.PI * a1 / 180) * (r + d) + X, -Math.Sin(Math.PI * a1 / 180) * (r + d) + Y);
            p4 = new Point(Math.Cos(Math.PI * a2 / 180) * (r + d) + X, -Math.Sin(Math.PI * a2 / 180) * (r + d) + Y);
            
            Point _p1 = new Point(Math.Cos(Math.PI * a1 / 180) * r + X, -Math.Sin(Math.PI * a1 / 180) * r + Y);

            Point _p2 = new Point(Math.Cos(Math.PI * a2 / 180) * r + X, -Math.Sin(Math.PI * a2 / 180) * r + Y);

            Segment2.StartPoint = p3;
            Segment2.Segments.Add(new ArcSegment(p4, S, 0, false, SweepDirection.Counterclockwise, true));

            PathGeometry CilclePathGeometry = new PathGeometry();
            CilclePathGeometry.Figures.Add(Segment1);
            CilclePathGeometry.Figures.Add(Segment2);

            System.Windows.Shapes.Path CirclePath = new System.Windows.Shapes.Path();
            CirclePath.Stroke = ItemColor;
            CirclePath.StrokeThickness = 1;
            CirclePath.Data = CilclePathGeometry;

            PrimitivesCanvas.Children.Add(CirclePath); // add rails

            PathGeometry ClipCilclePathGeometry = new PathGeometry();

            PathFigure CilclePath = new PathFigure();
            CilclePath.StartPoint = p1;
            s = r - d;
            S = new Size(s, s);
            CilclePath.Segments.Add(new ArcSegment(p2, S, 0, false, SweepDirection.Counterclockwise, true));
            CilclePath.Segments.Add(new LineSegment(p4, false));

            s = r + d;
            S = new Size(s, s);
            CilclePath.Segments.Add(new ArcSegment(p3, S, 0, false, SweepDirection.Clockwise, true));
            ClipCilclePathGeometry.Figures.Add(CilclePath);

            double angle;
            Line LineItem;

            double a = 360 / (2 * Math.PI * (r / PrimitivesScale) * 10 / sld); // step line

            //angle = Math.Ceiling((a1 - a / 2) / a) * a + a / 2;

            angle = a1 + a / 2;
            double x1, y1;
            while (angle < a2)
            {
                x1 = Math.Cos(Math.PI * angle / 180) * r + x;
                y1 = -Math.Sin(Math.PI * angle / 180) * r + y;
                LineItem = helper.CreateLine(x, y, x1, y1, ItemColor, 0.5);
                LineItem.Clip = ClipCilclePathGeometry;
                PrimitivesCanvas.Children.Add(LineItem);

                angle += a;
            }
        }

    }
}
