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

namespace track
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        

        public int PrimitivesScale = 1;

        public int FieldSize = 100;

        public int sld = 10;

        Boolean WriteGrid = false;
                
        public MainWindow()
        {
            InitializeComponent();

            if (WriteGrid)
            {
                Line LineItem1 = new Line();
                LineItem1.X1 = 0;
                LineItem1.Y1 = 0;
                LineItem1.X2 = 1024;
                LineItem1.Y2 = 768;
                LineItem1.Stroke = Brushes.Blue;
                PrimitivesCanvas.Children.Add(LineItem1);

                Line LineItem2 = new Line();
                LineItem2.X1 = 1024;
                LineItem2.Y1 = 0;
                LineItem2.X2 = 0;
                LineItem2.Y2 = 768;
                LineItem2.Stroke = Brushes.Red;
                PrimitivesCanvas.Children.Add(LineItem2);

                double LineWidth = 0.3;
            
                for (int i = 0; i < FieldSize; i++)
                {
                    PrimitivesCanvas.Children.Add(CreateLine(i * 10, 0, i * 10, FieldSize * 10, Brushes.Aqua, LineWidth));
                    PrimitivesCanvas.Children.Add(CreateLine(0, i * 10, FieldSize * 10, i * 10, Brushes.Aqua, LineWidth));
                }
            }

            ItemHV();

            Item45135();

            double l = 36.869;

            CircleTrack("BaseCircle0Track", 50, 0, l); // 1
            CircleTrack("BaseCircle1Track", 50, 90 - l, 90); // 2
            CircleTrack("BaseCircle2Track", 50, 90, 90 + l); // 3
            CircleTrack("BaseCircle3Track", 50, 180 - l, 180); // 4
            CircleTrack("BaseCircle4Track", 50, 180, 180 + l); // 5
            CircleTrack("BaseCircle5Track", 50, 270 - l, 270); // 6
            CircleTrack("BaseCircle6Track", 50, 270, 270 + l); // 7
            CircleTrack("BaseCircle7Track", 50, 360 - l, 360); // 8

            CircleTrack("SmallCircle0Track", 20, 0, 90);
            CircleTrack("SmallCircle1Track", 20, 90, 180);
            CircleTrack("SmallCircle2Track", 20, 180, 270);
            CircleTrack("SmallCircle3Track", 20, 270, 360);      
        }

        public void CircleTrack(string var, int r, double a1, double a2)
        {
            r = r * PrimitivesScale;

            List<String> items = new List<String>();

            double angle;
            
            double a = 360 / (2 * Math.PI * (r / PrimitivesScale) * 10 / sld);

            //angle = a1 + a / 2;

            angle = a1 + a;

            double x1, y1, px, py, dx, dy, dtx, dty;

            px = Math.Cos(Math.PI * a1 / 180) * r;
            py = Math.Sin(Math.PI * a1 / 180) * r;

            while (angle < a2 - a / 2)
            {
                
                
                x1 = Math.Cos(Math.PI * angle / 180) * r;
                y1 = Math.Sin(Math.PI * angle / 180) * r;

                dtx = x1 - px;
                dty = y1 - py;

                //px = x1;
                //py = y1;
                
                    //Math.Round(dtx, 2)
                items.Add("{" + Str(dtx) + ", " + Str(dty) + "}");

                angle += a;
            }

            string lua = var + " = {";
            string[] lua_items = items.ToArray();
            lua = lua + String.Join(", ", lua_items) + "}";
            Console.WriteLine(lua);
        }

        public void Item45135()
        {
            List<String> items45 = new List<String>();
            List<String> items135 = new List<String>();

            double sldt = sld / Math.Sqrt(2) / 10;
            
            double i = 1;
            double l = i * sldt;

            while (l < 9.5)
            {   
                //items45.Add("{" + Math.Round((sldt * PrimitivesScale),2) + ", " + Math.Round((sldt * PrimitivesScale),2) + "}");
                //items135.Add("{" + Math.Round((sldt * PrimitivesScale), 2) + ", " + (- Math.Round((sldt * PrimitivesScale), 2)) + "}");

                items45.Add("{" + Str(sldt * i * PrimitivesScale) + ", " + Str(sldt * i * PrimitivesScale) + "}");
                items135.Add("{" + Str(sldt * i * PrimitivesScale) + ", " + Str(-(sldt * i * PrimitivesScale)) + "}");
                
                i++;

                l = i * sldt;

            }

            string lua45 = "Item45Track = {";
            string[] lua_items45 = items45.ToArray();
            lua45 = lua45 + String.Join(", ", lua_items45) + "}";
            Console.WriteLine(lua45);

            string lua135 = "Item135Track = {";
            string[] lua_items135 = items135.ToArray();
            lua135 = lua135 + String.Join(", ", lua_items135) + "}";
            Console.WriteLine(lua135); 
        }

        public void ItemHV()
        {
            double sldt = sld / 10;
            double i = 1;
            double l = i * sldt;

            List<String> itemsH =  new List<String>();
            List<String> itemsV = new List<String>();

            while (l < 10)
            {   
                
                //itemsH.Add("{" + (sldt * PrimitivesScale) + ", 0}");
                //itemsV.Add("{0, " + (sldt * PrimitivesScale) + "}");

                itemsH.Add("{" + (l * PrimitivesScale) + ", 0}");
                itemsV.Add("{0, -" + (l * PrimitivesScale) + "}");

                i++;
                l = i * sldt;
                
            }

            string luaH = "HorizontalTrack = {";
            string[] lua_itemsH = itemsH.ToArray();
            luaH = luaH + String.Join(", ", lua_itemsH) + "}";
            Console.WriteLine(luaH); 

            string luaV = "VerticalTrack = {";
            string[] lua_itemsV = itemsV.ToArray();
            luaV = luaV + String.Join(", ", lua_itemsV) + "}";
            Console.WriteLine(luaV);
        }

        public Line CreateLine(double x1, double y1, double x2, double y2, Brush LineColor, double Thickness)
        {
            Line LineItem = new Line();
            LineItem.X1 = x1 * PrimitivesScale;
            LineItem.Y1 = y1 * PrimitivesScale;
            LineItem.X2 = x2 * PrimitivesScale;
            LineItem.Y2 = y2 * PrimitivesScale;
            LineItem.StrokeThickness = Thickness;
            LineItem.Stroke = LineColor;
            return LineItem;
        }

        public String Str(double num)
        {
            String res;
            num = Math.Round(num, 2);
            res = num.ToString();
            res = res.Replace(",", ".");
            return res;
        }
    }
}
