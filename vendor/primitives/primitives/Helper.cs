using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;
using System.Windows.Media;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Media.Imaging;
using System.Windows.Input;
using System.IO;

namespace primitives
{

    class Helper
    {
        private int _PrimitivesScale;
        private int _FieldSize;
        private Boolean _SaveImages;
        private Boolean _WriteGrid;
        private Canvas _PrimitivesCanvas;
        private string _ResourcesPath = "f:\\projects\\trains\\Platforms\\cpp\\MyTrains\\vendor\\primitives\\";

        public void SetCanvas(Canvas canvas)
        {
            this._PrimitivesCanvas = canvas;

            this._PrimitivesCanvas.MouseDown += btn1_Click;
        }

        public Helper(int PrimitivesScale, int FieldSize, Boolean SaveImages, Boolean WriteGrid)
        {
            this._PrimitivesScale = PrimitivesScale;
            this._FieldSize = FieldSize;
            this._SaveImages = SaveImages;
            this._WriteGrid = WriteGrid;
        }

        public void WriteGrid()
        {
            if (_WriteGrid)
            {
                Line LineItem1 = new Line();
                LineItem1.X1 = 0;
                LineItem1.Y1 = 0;
                LineItem1.X2 = 1024;
                LineItem1.Y2 = 768;
                LineItem1.Stroke = Brushes.Blue;
                _PrimitivesCanvas.Children.Add(LineItem1);

                Line LineItem2 = new Line();
                LineItem2.X1 = 1024;
                LineItem2.Y1 = 0;
                LineItem2.X2 = 0;
                LineItem2.Y2 = 768;
                LineItem2.Stroke = Brushes.Red;
                _PrimitivesCanvas.Children.Add(LineItem2);

                for (int i = 0; i < _FieldSize; i++)
                {
                    _PrimitivesCanvas.Children.Add(CreateLine(i * 10, 0, i * 10, _FieldSize * 10, Brushes.Aqua, 1));
                    _PrimitivesCanvas.Children.Add(CreateLine(0, i * 10, _FieldSize * 10, i * 10, Brushes.Aqua, 1));
                }
            }
        }

        public Line CreateLine(double x1, double y1, double x2, double y2, Brush LineColor, double Thickness)
        {
            Line LineItem = new Line();
            LineItem.X1 = x1 * _PrimitivesScale;
            LineItem.Y1 = y1 * _PrimitivesScale;
            LineItem.X2 = x2 * _PrimitivesScale;
            LineItem.Y2 = y2 * _PrimitivesScale;
            LineItem.StrokeThickness = Thickness;
            LineItem.Stroke = LineColor;
            return LineItem;
        }

        public void ExportToPng(string FileName, int ImageWidth, int ImageHeight)
        {
            if (this._SaveImages)
            {
                Canvas element = _PrimitivesCanvas;

                string FilePath = _ResourcesPath + FileName;
                // Save current canvas transform
                Transform transform = element.LayoutTransform;
                // reset current transform (in case it is scaled or rotated)
                element.LayoutTransform = null;

                // Get the size of canvas
                //Size size = new Size(surface.Width, surface.Height);
                Size size = new Size(ImageWidth, ImageHeight);
                // Measure and arrange the surface
                // VERY IMPORTANT

                //ImgRect.Location = new Point(50, 50);

                element.Measure(size);
                element.Arrange(new Rect(size));

                // Create a render bitmap and push the surface to it
                RenderTargetBitmap renderBitmap =
                  new RenderTargetBitmap(
                    (int)size.Width,
                    (int)size.Height,
                    96d,
                    96d,
                    PixelFormats.Pbgra32);
                
                element.UpdateLayout();
                renderBitmap.Render(element);
                
                // Create a file stream for saving image
                using (FileStream outStream = new FileStream(FilePath, FileMode.Create))
                {
                    // Use png encoder for our data
                    PngBitmapEncoder encoder = new PngBitmapEncoder();
                    // push the rendered bitmap to it
                    encoder.Frames.Add(BitmapFrame.Create(renderBitmap));
                    // save the data to the stream
                    encoder.Save(outStream);
                }

                // Restore previously saved layout
                element.LayoutTransform = transform;
            }
        }

        public double l(double l)
        {
            return l * _PrimitivesScale;
        }

        public VisualBrush GetHatchBrush(Brush color)
        {
            double StrokeThickness = 0.5;

            Line line = new Line();
            line.X1 = 10;
            line.Y1 = 0;
            line.X2 = 0;
            line.Y2 = 10;
            line.StrokeThickness = StrokeThickness;
            line.Stroke = color;

            Line line1 = new Line();
            line1.X1 = 1;
            line1.Y1 = -1;
            line1.X2 = -1;
            line1.Y2 = 1;
            line1.StrokeThickness = StrokeThickness;
            line1.Stroke = color;

            Line line2 = new Line();
            line2.X1 = 11;
            line2.Y1 = 9;
            line2.X2 = 9;
            line2.Y2 = 11;
            line2.StrokeThickness = StrokeThickness;
            line2.Stroke = color;

            RectangleGeometry rectangleGeometry = new RectangleGeometry();
            rectangleGeometry.Rect = new Rect(0, 0, 10, 10);
            
            Canvas hatchCanvas = new Canvas();
            hatchCanvas.Children.Add(line);
            hatchCanvas.Children.Add(line1);
            hatchCanvas.Children.Add(line2);
            hatchCanvas.Clip = rectangleGeometry;
            
            hatchCanvas.Width = 10;
            hatchCanvas.Height = 10;
            
            VisualBrush hatchBrush = new VisualBrush();
            hatchBrush.Visual = null;
            hatchBrush.Visual = hatchCanvas;
            hatchBrush.Viewport = new Rect(0, 0, 7, 7);
            hatchBrush.Viewbox = new Rect(0, 0, 10, 10);
            hatchBrush.TileMode = TileMode.Tile;
            hatchBrush.ViewboxUnits = BrushMappingMode.Absolute;
            hatchBrush.ViewportUnits = BrushMappingMode.Absolute;
            


            return hatchBrush;
        }
      
        private void btn1_Click(object sender, MouseButtonEventArgs e)
        {
            Point p = e.GetPosition(this._PrimitivesCanvas);
            Console.WriteLine("Click X=" + (p.X / this._PrimitivesScale) + "X = " + (p.Y / this._PrimitivesScale));
        }
    }
}
