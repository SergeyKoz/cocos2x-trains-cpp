#include "Cell.h"
#include "Field.h"
#include "Path.h"
#include "Cmd.h"

namespace GameObjects {

	Path::Path()
	{
		Field *Game = Field::getInstance();
		Size visibleSize = Director::getInstance()->getVisibleSize();		
		size = { (int)(visibleSize.width / (Game->scale * 10)), (int)(visibleSize.height / (Game->scale * 10)) };
		Graph = new GraphItem*[size.width];
		for (int i = 0; i < size.width; i++)
		{
			Graph[i] = new GraphItem[size.height];
		}
	}


	Path::~Path()
	{
	}

	const MapPoint Path::closer[20] = {
		{ 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
		{ 1, 1 }, { -1, 1 }, { -1, 1 }, { -1, -1 },
		{ 2, 2 }, { -2, 2 }, { -2, 2 }, { -2, -2 },
		{ 1, 3 }, { -1, 3 }, { -1, 3 }, { -1, -3 },
		{ 3, 1 }, { -3, 1 }, { -3, 1 }, { -3, -1 }
	};

	bool Path::Init(MapPoint Point){
		bool f = false;
		Field *Game = Field::getInstance();
		
		Vec2 layerPosition = Game->mapLayer->getPosition();
		origin = { (int)round(layerPosition.x / (Game->scale * 10)), (int)round(layerPosition.y / (Game->scale * 10)) };

		Cell *startCell = &Game->cells[Point.x][Point.y];

		Area.e = { -1, -1 };
		int p = -1;
		if (startCell->configuration == Polar || startCell->configuration == Ortogonal){
			for (int i = 0; i < 8; i++){
				if (startCell->straightConnection[i] == 0 && !(startCell->straightConnection[Cell::Related[i]] == 0)){
					p = i;
				}
			}
		}
		if (p >= 0){			
			Area.s = Point;
			Area.sc = startCell;
			graph(Point)->p = Point;
			for (int i = 0; i < 8; i++){
				graph(Point)->f[i] = false;
				graph(Point)->d[i] = 0;
				graph(Point)->In[i] = 0;
				graph(Point)->Out[i] = -1;
			}
			graph(Point)->d[p] = 1;
			graph(Point)->d[Cell::Related[p]] = 2;
			graph(Point)->isArea = true;
			GraphItems.insert(GraphItems.end(), graph(Point));			
			f = true;
		}
		return f;
	}

	void Path::Show(MapPoint Point){
		bool changed = false;

		if (Point.x + origin.x < 0) {
			Point.x = - origin.x;
		}

		if (Point.x + origin.x > size.width - 1) {
			Point.x = size.width - origin.x - 1;
		}

		if (Point.y + origin.y < 0) {
			Point.y = - origin.y;
		}

		if (Point.y + origin.y > size.height - 1) {
			Point.y = size.height - origin.y - 1;
		}

		if ((Area.e.x == -1 && !(Area.s.x == Point.x && Area.s.y == Point.y)) || 
			(Area.e.x >= 0 && !(Area.e.x == Point.x && Area.e.y == Point.y))){
			changed = true;
		}
		if (changed){
			Area.d.x = Point.x - Area.s.x;
			Area.d.y = Point.y - Area.s.y;			
			Area.e = Point;
			Area.dt = abs(sqrt(pow(Area.d.x, 2) + pow(Area.d.y, 2)));			
			Area.sin = (float)Area.d.y / (float)Area.dt;
			Area.cos = (float)Area.d.x / (float)Area.dt;
			MapPoint d;
			for (auto i = BorderItems.begin(); i != BorderItems.end();){
				if (Path::IsArea(*i)){
					for (auto c = 0; c < 20; c++){						
						d = { i->x + closer[c].x, i->y + closer[c].y };
						if (Path::inWindow(d)){
							if (graph(d)->isArea){
								if (!graph(d)->isInside){
									for (auto j = 0; j < 8; j++){
										graph(d)->f[j] = false;
									}
									InsideItems.insert(InsideItems.end(), d);
									graph(d)->isInside = true;
								}
							}
							graph(*i)->isBorder = false;
						}
					}
					i = BorderItems.erase(i);
				} else {
					++i;
				}
			}			
			if (InsideItems.size()>0){
				GraphItems.clear();
				for (auto i = 0; i < InsideItems.size(); i++){					
					graph(InsideItems[i])->isInside = false;
					GraphItems.insert(GraphItems.end(), graph(InsideItems[i]));
				}
				InsideItems.clear();
			}
			Find(Area.sc);
			Field *Game = Field::getInstance();
			Cell *current = &Game->cells[Point.x][Point.y];
			if (graph(Point)->isArea){
				int min = 0, p = -1;
				for (int c = 0; c < 8; c++){
					if (graph(Point)->Out[c] >= 0 && graph(Point)->f[c] && graph(Point)->d[c] > 0 && (min == 0 || graph(Point)->d[c] < min)){
						min = graph(Point)->d[c];
						p = c;
					}
				}
				for (auto c = 0; c < PathItems.size(); c++){
					Game->mapLayer->removeChild(PathItems[c]->element, true);
				}
				PathItems.clear();
				if (p >= 0 && (Area.d.x != 0 || Area.d.y != 0)) {
					int i = 0;
					int nextPoint;
					Cell *next;
					ConnectionConfig *connect;
					PathItem *item;
					MapPoint c = { current->x, current->y }, n;					
					while (graph(c)->d[p] > 0 && graph(c)->In[p] != 0) {						
						next = graph(c)->In[p];
						n = { next->x, next->y };
						nextPoint = Cell::Related[graph(c)->Out[p]];
						d.x = n.x - c.x;
						d.y = n.y - c.y;
						connect = Cell::GetConnectConfig(d.x, d.y, p);
						item = new PathItem;
						item->elementType = connect->element;
						if (connect->enter == 0) {
							item->element = Elements::GetTrackElement(c, connect->element);
						}
						else {
							item->element = Elements::GetTrackElement(n, connect->element);
						}
						item->enter = connect->enter;
						item->next = next;
						item->current = current;						
						item->point = p;
						PathItems.insert(PathItems.end(), item);
						p = nextPoint;
						current = next;
						c = { current->x, current->y };
						i++;
					}
					for (auto c = 0; c < PathItems.size(); c++){
						Game->mapLayer->addChild(PathItems[c]->element, ZIndexRails);
					}
				}
			}
		}
	}

	void Path::Set() {
		vector<string> commands;
		string pathCommand = "";
		string switchCommand = "";
		int fromPoint, toPoint;
		Field *Game = Field::getInstance();
		for (auto c = 0; c < PathItems.size(); c++) {
			Game->mapLayer->removeChild(PathItems[c]->element, true);

			fromPoint = PathItems[c]->point;
			toPoint = Elements::offset[Elements::second[PathItems[c]->enter]][PathItems[c]->elementType].p;

			pathCommand += StringUtils::format("%s{\"from\":{\"x\":%d,\"y\":%d},\"to\":{\"x\":%d,\"y\":%d},\"point\":%d}",
				pathCommand == "" ? "" : ",", PathItems[c]->next->x, PathItems[c]->next->y, PathItems[c]->current->x, PathItems[c]->current->y, fromPoint);

			if (PathItems[c]->current->straightConnection[fromPoint] != NULL && PathItems[c]->current->divergingConnection[fromPoint] == NULL) {
				switchCommand += StringUtils::format("%s{\"cell\":{\"x\":%d,\"y\":%d},\"point\":%d}",
					switchCommand == "" ? "" : ",", PathItems[c]->current->x, PathItems[c]->current->y, fromPoint);
			}

			if (PathItems[c]->next->straightConnection[toPoint] != NULL && PathItems[c]->next->divergingConnection[toPoint] == NULL) {
				switchCommand += StringUtils::format("%s{\"cell\":{\"x\":%d,\"y\":%d},\"point\":%d}",
					switchCommand == "" ? "" : ",", PathItems[c]->next->x, PathItems[c]->next->y, toPoint);
			}
		}
		string command;
		PathItems.clear();
		if (pathCommand != "") {
			command = "path --add --path=[" + pathCommand + "]";
			Cmd::Exec(command);
		}

		if (switchCommand != "") {
			command = "path --add --switch=[" + switchCommand + "]";
			Cmd::Exec(command);
		}

		for (int x = 0; x < (int)size.width; x++){
			for (int y = 0; y < (int)size.height; y++){
				Graph[x][y].isArea = false;
				for (int c = 0; c < 8; c++){
					Graph[x][y].d[c] = 0;
					Graph[x][y].f[c] = false;
					Graph[x][y].In[c] = 0;
					Graph[x][y].Out[c] = -1;
				}
			}
		}
		GraphItems.clear();
		for (auto i = 0; i < BorderItems.size(); i++){			
			graph(BorderItems[i])->isBorder = false;
		}
		BorderItems.clear();
		Area.e = { -1, -1 };
	}

	void Path::Find(Cell *c, int p){
		Field *Game = Field::getInstance();
		if (p >= 0){			
			int d = graph({c->x, c->y})->d[p];
			if (p == 0){
				Connect(c, p, SmallCilcleSect3, d + 314, 0);
				Connect(c, p, BaseCircleSect6, d + 321, 0);
				Connect(c, p, Horizontal, d + 100, 0);
				Connect(c, p, BaseCircleSect1, d + 321, 1);
				Connect(c, p, SmallCilcleSect0, d + 314, 1);
			}
			if (p == 1){
				Connect(c, p, BaseCircleSect7, d + 321, 0);
				Connect(c, p, Item45, d + 141, 0);
				Connect(c, p, BaseCircleSect2, d + 321, 1);
			}
			if (p == 2){
				Connect(c, p, SmallCilcleSect0, d + 314, 0);
				Connect(c, p, BaseCircleSect0, d + 321, 0);
				Connect(c, p, Vertical, d + 100, 1);
				Connect(c, p, BaseCircleSect3, d + 321, 1);
				Connect(c, p, SmallCilcleSect1, d + 314, 1);
			}
			if (p == 3){
				Connect(c, p, BaseCircleSect4, d + 321, 1);
				Connect(c, p, Item135, d + 141, 1);
				Connect(c, p, BaseCircleSect1, d + 321, 0);
			}
			if (p == 4){
				Connect(c, p, SmallCilcleSect2, d + 314, 1);
				Connect(c, p, BaseCircleSect5, d + 321, 1);
				Connect(c, p, Horizontal, d + 100, 1);
				Connect(c, p, BaseCircleSect2, d + 321, 0);
				Connect(c, p, SmallCilcleSect1, d + 314, 0);
			}
			if (p == 5){
				Connect(c, p, BaseCircleSect3, d + 321, 0);
				Connect(c, p, Item45, d + 141, 1);
				Connect(c, p, BaseCircleSect6, d + 321, 1);
			}
			if (p == 6){
				Connect(c, p, SmallCilcleSect3, d + 314, 1);
				Connect(c, p, BaseCircleSect7, d + 321, 1);
				Connect(c, p, Vertical, d + 100, 0);
				Connect(c, p, BaseCircleSect4, d + 321, 0);
				Connect(c, p, SmallCilcleSect2, d + 314, 0);
			}
			if (p == 7){
				Connect(c, p, BaseCircleSect0, d + 321, 1);
				Connect(c, p, Item135, d + 141, 0);
				Connect(c, p, BaseCircleSect5, d + 321, 0);
			}
		}
		int min = 0;
		int enter;
		MapPoint next;
		for (auto i = 0; i < GraphItems.size(); i++){
			for (int c = 0; c < 8; c++){
				if (!GraphItems[i]->f[c] && GraphItems[i]->d[c] > 0 && (min == 0 || GraphItems[i]->d[c] < min)){
					min = GraphItems[i]->d[c];
					next = GraphItems[i]->p;
					enter = c;
				}
			}
		}
		if (min > 0){
			graph(next)->f[enter] = true;
			if (graph(next)->In[enter] != 0){
				int nextEnter = Cell::Related[enter];
				Cell *out = graph(next)->In[enter];
				graph({ out->x, out->y })->f[enter] = true;
				graph(next)->f[nextEnter] = true;
				graph(next)->d[nextEnter] = min + 1;
				Find(&Game->cells[next.x][next.y], nextEnter);
			}else{
				Find(&Game->cells[next.x][next.y], enter);
			}
		}
	}

	void Path::Connect(Cell *out, int outPoint, TrackElement element, int d, int enter){
		MapPoint p = { out->x + Elements::offset[enter][element].dx, out->y + Elements::offset[enter][element].dy };
		
		if (Path::inWindow(p)){
			if (Path::IsArea(p)){
				Cell *in = &Field::getInstance()->cells[p.x][p.y];
				int inPoint = Elements::offset[enter][element].p;
				if (in->isAllow(Elements::offset[enter][element].p, element)){
					GraphItem *i = graph({ in->x, in->y });
					if (i->d[inPoint] == 0 || (i->d[inPoint] > 0 && i->d[inPoint] > d)){
						i->d[inPoint] = d;
						i->In[inPoint] = out;
						i->Out[inPoint] = outPoint;
					}
				}
			} else {
				if (!graph(p)->isBorder && (element == Horizontal || element == Vertical || element == Item45 || element == Item135)){
					BorderItems.insert(BorderItems.end(), p);
					graph(p)->isBorder = true;
				}				
			}
		}
	}

	bool Path::IsArea(MapPoint Point){
		bool f = false;
		if (graph(Point)->isArea){
			f = true;
		} else {
			Vec2 m = {
				(Point.x - Area.s.x) * Area.cos - (Area.s.y - Point.y) * Area.sin,
				(Point.x - Area.s.x) * Area.sin + (Area.s.y - Point.y) * Area.cos
			};
			if (m.x > -Area.Width && m.x < Area.Width + Area.dt && m.y > -Area.Width && m.y < Area.Width){
				f = true;
				graph(Point)->p = Point;
				graph(Point)->isArea = true;
				for (int i = 0; i < 8; i++){
					graph(Point)->f[i] = false;
					graph(Point)->In[i] = 0;
					graph(Point)->Out[i] = -1;
					graph(Point)->d[i] = 0;
				}
				GraphItems.insert(GraphItems.end(), graph(Point));
			}
		}
		return f;
	}

	GraphItem *Path::graph(MapPoint Point){
		return &Graph[Point.x + origin.x][Point.y + origin.y];
	}

	bool Path::inWindow(MapPoint Point){
		return (Point.x + origin.x) > 0 && (Point.y + origin.y) > 0 && (Point.x + origin.x) < size.width && (Point.y + origin.y) < size.height;
	}
}
