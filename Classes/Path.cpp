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

	const TrackItem Path::track[16] = {		
		{ 0, { { 0, 0 }, { 0, -1 },{ 0, -2 },{ 0, -3 },{ 0, -4 },{ 0, -5 },{ 0, -6 },{ 0, -7 },{ 0, -8 },{ 0, -9 } } },
		{ 0, { { 0, 0 },{ 1, 0 },{ 2, 0 },{ 3, 0 },{ 4, 0 },{ 5, 0 },{ 6, 0 },{ 7, 0 },{ 8, 0 },{ 9, 0 } } },
		{ 0, { { 0, 0 },{ 0.71f, 0.71f },{ 1.41f, 1.41f },{ 2.12f, 2.12f },{ 2.83f, 2.83f },{ 3.54f, 3.54f },{ 4.24f, 4.24f },{ 4.95f, 4.95f },{ 5.66f, 5.66f },{ 6.36f, 6.36f },{ 7.07f, 7.07f },{ 7.78f, 7.78f },{ 8.49f, 8.49f },{ 9.19f, 9.19f } } },
		{ 0, { { 0, 0 },{ 0.71f, -0.71f },{ 1.41f, -1.41f },{ 2.12f, -2.12f },{ 2.83f, -2.83f },{ 3.54f, -3.54f },{ 4.24f, -4.24f },{ 4.95f, -4.95f },{ 5.66f, -5.66f },{ 6.36f, -6.36f },{ 7.07f, -7.07f },{ 7.78f, -7.78f },{ 8.49f, -8.49f },{ 9.19f, -9.19f } } },
		//13
		{ 10, { { 0, 0 },{ -0.01f, 1 },{ -0.04f, 2 },{ -0.09f, 3 },{ -0.16f, 4 },{ -0.25f, 4.99f },{ -0.36f, 5.99f },{ -0.49f, 6.98f },{ -0.64f, 7.97f },{ -0.81f, 8.95f },{ -1, 9.93f },{ -1.21f, 10.91f },{ -1.43f, 11.89f },{ -1.68f, 12.85f },{ -1.95f, 13.82f },{ -2.23f, 14.78f },{ -2.54f, 15.73f },{ -2.86f, 16.67f },{ -3.21f, 17.61f },{ -3.57f, 18.55f },{ -3.95f, 19.47f },{ -4.35f, 20.39f },{ -4.76f, 21.3f },{ -5.2f, 22.2f },{ -5.65f, 23.09f },{ -6.12f, 23.97f },{ -6.61f, 24.84f },{ -7.11f, 25.71f },{ -7.64f, 26.56f },{ -8.18f, 27.4f },{ -8.73f, 28.23f },{ -9.31f, 29.05f } } },
		{ 10, { { 0, 0 },{ -0.81f, 0.59f },{ -1.62f, 1.17f },{ -2.45f, 1.73f },{ -3.29f, 2.27f },{ -4.14f, 2.8f },{ -5, 3.3f },{ -5.88f, 3.79f },{ -6.76f, 4.27f },{ -7.65f, 4.72f },{ -8.54f, 5.16f },{ -9.45f, 5.58f },{ -10.37f, 5.98f },{ -11.29f, 6.37f },{ -12.22f, 6.73f },{ -13.16f, 7.08f },{ -14.11f, 7.41f },{ -15.06f, 7.71f },{ -16.01f, 8 },{ -16.98f, 8.27f },{ -17.95f, 8.52f },{ -18.92f, 8.76f },{ -19.9f, 8.97f },{ -20.88f, 9.16f },{ -21.86f, 9.33f },{ -22.85f, 9.49f },{ -23.84f, 9.62f },{ -24.83f, 9.73f },{ -25.83f, 9.83f },{ -26.83f, 9.9f },{ -27.83f, 9.95f },{ -28.83f, 9.99f } } },
		{ 10, { { 0, 0 },{ -1, -0.01f },{ -2, -0.04f },{ -3, -0.09f },{ -4, -0.16f },{ -4.99f, -0.25f },{ -5.99f, -0.36f },{ -6.98f, -0.49f },{ -7.97f, -0.64f },{ -8.95f, -0.81f },{ -9.93f, -1 },{ -10.91f, -1.21f },{ -11.89f, -1.43f },{ -12.85f, -1.68f },{ -13.82f, -1.95f },{ -14.78f, -2.23f },{ -15.73f, -2.54f },{ -16.67f, -2.86f },{ -17.61f, -3.21f },{ -18.55f, -3.57f },{ -19.47f, -3.95f },{ -20.39f, -4.35f },{ -21.3f, -4.76f },{ -22.2f, -5.2f },{ -23.09f, -5.65f },{ -23.97f, -6.12f },{ -24.84f, -6.61f },{ -25.71f, -7.11f },{ -26.56f, -7.64f },{ -27.4f, -8.18f },{ -28.23f, -8.73f },{ -29.05f, -9.31f } } },
		{ 10, { { 0, 0 },{ -0.59f, -0.81f },{ -1.17f, -1.62f },{ -1.73f, -2.45f },{ -2.27f, -3.29f },{ -2.8f, -4.14f },{ -3.3f, -5 },{ -3.79f, -5.88f },{ -4.27f, -6.76f },{ -4.72f, -7.65f },{ -5.16f, -8.54f },{ -5.58f, -9.45f },{ -5.98f, -10.37f },{ -6.37f, -11.29f },{ -6.73f, -12.22f },{ -7.08f, -13.16f },{ -7.41f, -14.11f },{ -7.71f, -15.06f },{ -8, -16.01f },{ -8.27f, -16.98f },{ -8.52f, -17.95f },{ -8.76f, -18.92f },{ -8.97f, -19.9f },{ -9.16f, -20.88f },{ -9.33f, -21.86f },{ -9.49f, -22.85f },{ -9.62f, -23.84f },{ -9.73f, -24.83f },{ -9.83f, -25.83f },{ -9.9f, -26.83f },{ -9.95f, -27.83f },{ -9.99f, -28.83f } } },
		{ 10, { { 0, 0 },{ 0.01f, -1 },{ 0.04f, -2 },{ 0.09f, -3 },{ 0.16f, -4 },{ 0.25f, -4.99f },{ 0.36f, -5.99f },{ 0.49f, -6.98f },{ 0.64f, -7.97f },{ 0.81f, -8.95f },{ 1, -9.93f },{ 1.21f, -10.91f },{ 1.43f, -11.89f },{ 1.68f, -12.85f },{ 1.95f, -13.82f },{ 2.23f, -14.78f },{ 2.54f, -15.73f },{ 2.86f, -16.67f },{ 3.21f, -17.61f },{ 3.57f, -18.55f },{ 3.95f, -19.47f },{ 4.35f, -20.39f },{ 4.76f, -21.3f },{ 5.2f, -22.2f },{ 5.65f, -23.09f },{ 6.12f, -23.97f },{ 6.61f, -24.84f },{ 7.11f, -25.71f },{ 7.64f, -26.56f },{ 8.18f, -27.4f },{ 8.73f, -28.23f },{ 9.31f, -29.05f } } },
		{ 10, { { 0, 0 },{ 0.81f, -0.59f },{ 1.62f, -1.17f },{ 2.45f, -1.73f },{ 3.29f, -2.27f },{ 4.14f, -2.8f },{ 5, -3.3f },{ 5.88f, -3.79f },{ 6.76f, -4.27f },{ 7.65f, -4.72f },{ 8.54f, -5.16f },{ 9.45f, -5.58f },{ 10.37f, -5.98f },{ 11.29f, -6.37f },{ 12.22f, -6.73f },{ 13.16f, -7.08f },{ 14.11f, -7.41f },{ 15.06f, -7.71f },{ 16.01f, -8 },{ 16.98f, -8.27f },{ 17.95f, -8.52f },{ 18.92f, -8.76f },{ 19.9f, -8.97f },{ 20.88f, -9.16f },{ 21.86f, -9.33f },{ 22.85f, -9.49f },{ 23.84f, -9.62f },{ 24.83f, -9.73f },{ 25.83f, -9.83f },{ 26.83f, -9.9f },{ 27.83f, -9.95f },{ 28.83f, -9.99f } } },
		{ 10, { { 0, 0 },{ 1, 0.01f },{ 2, 0.04f },{ 3, 0.09f },{ 4, 0.16f },{ 4.99f, 0.25f },{ 5.99f, 0.36f },{ 6.98f, 0.49f },{ 7.97f, 0.64f },{ 8.95f, 0.81f },{ 9.93f, 1 },{ 10.91f, 1.21f },{ 11.89f, 1.43f },{ 12.85f, 1.68f },{ 13.82f, 1.95f },{ 14.78f, 2.23f },{ 15.73f, 2.54f },{ 16.67f, 2.86f },{ 17.61f, 3.21f },{ 18.55f, 3.57f },{ 19.47f, 3.95f },{ 20.39f, 4.35f },{ 21.3f, 4.76f },{ 22.2f, 5.2f },{ 23.09f, 5.65f },{ 23.97f, 6.12f },{ 24.84f, 6.61f },{ 25.71f, 7.11f },{ 26.56f, 7.64f },{ 27.4f, 8.18f },{ 28.23f, 8.73f },{ 29.05f, 9.31f } } },
		{ 10, { { 0, 0 },{ 0.59f, 0.81f },{ 1.17f, 1.62f },{ 1.73f, 2.45f },{ 2.27f, 3.29f },{ 2.8f, 4.14f },{ 3.3f, 5 },{ 3.79f, 5.88f },{ 4.27f, 6.76f },{ 4.72f, 7.65f },{ 5.16f, 8.54f },{ 5.58f, 9.45f },{ 5.98f, 10.37f },{ 6.37f, 11.29f },{ 6.73f, 12.22f },{ 7.08f, 13.16f },{ 7.41f, 14.11f },{ 7.71f, 15.06f },{ 8, 16.01f },{ 8.27f, 16.98f },{ 8.52f, 17.95f },{ 8.76f, 18.92f },{ 8.97f, 19.9f },{ 9.16f, 20.88f },{ 9.33f, 21.86f },{ 9.49f, 22.85f },{ 9.62f, 23.84f },{ 9.73f, 24.83f },{ 9.83f, 25.83f },{ 9.9f, 26.83f },{ 9.95f, 27.83f },{ 9.99f, 28.83f } } },
		//10
		{ 7, { { 0, 0 },{ -0.02f, 1 },{ -0.1f, 2 },{ -0.22f, 2.99f },{ -0.4f, 3.97f },{ -0.62f, 4.95f },{ -0.89f, 5.91f },{ -1.21f, 6.86f },{ -1.58f, 7.79f },{ -1.99f, 8.7f },{ -2.45f, 9.59f },{ -2.95f, 10.45f },{ -3.49f, 11.29f },{ -4.08f, 12.1f },{ -4.7f, 12.88f },{ -5.37f, 13.63f },{ -6.07f, 14.35f },{ -6.8f, 15.03f },{ -7.57f, 15.67f },{ -8.37f, 16.27f },{ -9.19f, 16.83f },{ -10.05f, 17.35f },{ -10.93f, 17.82f },{ -11.83f, 18.26f },{ -12.75f, 18.64f },{ -13.69f, 18.98f },{ -14.65f, 19.27f },{ -15.62f, 19.51f },{ -16.6f, 19.71f },{ -17.59f, 19.85f },{ -18.59f, 19.95f } } },
		{ 7, { { 0, 0 },{ -1, -0.02f },{ -2, -0.1f },{ -2.99f, -0.22f },{ -3.97f, -0.4f },{ -4.95f, -0.62f },{ -5.91f, -0.89f },{ -6.86f, -1.21f },{ -7.79f, -1.58f },{ -8.7f, -1.99f },{ -9.59f, -2.45f },{ -10.45f, -2.95f },{ -11.29f, -3.49f },{ -12.1f, -4.08f },{ -12.88f, -4.7f },{ -13.63f, -5.37f },{ -14.35f, -6.07f },{ -15.03f, -6.8f },{ -15.67f, -7.57f },{ -16.27f, -8.37f },{ -16.83f, -9.19f },{ -17.35f, -10.05f },{ -17.82f, -10.93f },{ -18.26f, -11.83f },{ -18.64f, -12.75f },{ -18.98f, -13.69f },{ -19.27f, -14.65f },{ -19.51f, -15.62f },{ -19.71f, -16.6f },{ -19.85f, -17.59f },{ -19.95f, -18.59f } } },
		{ 7, { { 0, 0 },{ 0.02f, -1 },{ 0.1f, -2 },{ 0.22f, -2.99f },{ 0.4f, -3.97f },{ 0.62f, -4.95f },{ 0.89f, -5.91f },{ 1.21f, -6.86f },{ 1.58f, -7.79f },{ 1.99f, -8.7f },{ 2.45f, -9.59f },{ 2.95f, -10.45f },{ 3.49f, -11.29f },{ 4.08f, -12.1f },{ 4.7f, -12.88f },{ 5.37f, -13.63f },{ 6.07f, -14.35f },{ 6.8f, -15.03f },{ 7.57f, -15.67f },{ 8.37f, -16.27f },{ 9.19f, -16.83f },{ 10.05f, -17.35f },{ 10.93f, -17.82f },{ 11.83f, -18.26f },{ 12.75f, -18.64f },{ 13.69f, -18.98f },{ 14.65f, -19.27f },{ 15.62f, -19.51f },{ 16.6f, -19.71f },{ 17.59f, -19.85f },{ 18.59f, -19.95f } } },
		{ 7, { { 0, 0 },{ 1, 0.02f },{ 2, 0.1f },{ 2.99f, 0.22f },{ 3.97f, 0.4f },{ 4.95f, 0.62f },{ 5.91f, 0.89f },{ 6.86f, 1.21f },{ 7.79f, 1.58f },{ 8.7f, 1.99f },{ 9.59f, 2.45f },{ 10.45f, 2.95f },{ 11.29f, 3.49f },{ 12.1f, 4.08f },{ 12.88f, 4.7f },{ 13.63f, 5.37f },{ 14.35f, 6.07f },{ 15.03f, 6.8f },{ 15.67f, 7.57f },{ 16.27f, 8.37f },{ 16.83f, 9.19f },{ 17.35f, 10.05f },{ 17.82f, 10.93f },{ 18.26f, 11.83f },{ 18.64f, 12.75f },{ 18.98f, 13.69f },{ 19.27f, 14.65f },{ 19.51f, 15.62f },{ 19.71f, 16.6f },{ 19.85f, 17.59f },{ 19.95f, 18.59f } } }
	};

	bool Path::Init(MapPoint Point, int Enter){
		bool f = false;
		Field *Game = Field::getInstance();
		
		Vec2 layerPosition = Game->mapLayer->getPosition();
		origin = { (int)round(layerPosition.x / (Game->scale * 10)), (int)round(layerPosition.y / (Game->scale * 10)) };

		Cell *startCell = &Game->cells[Point.x][Point.y];

		Area.e = { -1, -1 };
		Area.p = -1;
		int p = -1;
		bool pf = false;
		if (startCell->configuration != None) {
			if (startCell->straightConnection[Enter] == 0 && !(startCell->straightConnection[Cell::Related[Enter]] == 0)) {
				pf = true;
			}
			if (startCell->straightConnection[Enter] != 0 && startCell->divergingConnection[Enter] == 0) {
				pf = true;
			}
		}

		if (pf) {
			Area.s = Point;
			Area.sc = startCell;
			graph(Point)->p = Point;
			for (int i = 0; i < 8; i++){
				graph(Point)->f[i] = false;
				graph(Point)->d[i] = 0;
				graph(Point)->In[i] = 0;
				graph(Point)->Out[i] = -1;
			}
			graph(Point)->d[Enter] = 1;
			graph(Point)->d[Cell::Related[Enter]] = 2;
			graph(Point)->isArea = true;
			GraphItems.insert(GraphItems.end(), graph(Point));			
			f = true;

			// debug
			//debugNode = DrawNode::create();
			//Game->mapLayer->addChild(debugNode, ZIndexRails);
		}
		return f;
	}

	void Path::Show(MapPoint Point, int Enter){
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

		MapPoint d;
		if (changed) {
			Area.d.x = Point.x - Area.s.x;
			Area.d.y = Point.y - Area.s.y;
			Area.e = Point;
			Area.dt = abs(sqrt(pow(Area.d.x, 2) + pow(Area.d.y, 2)));
			Area.sin = (float)Area.d.y / (float)Area.dt;
			Area.cos = (float)Area.d.x / (float)Area.dt;
			
			for (auto i = BorderItems.begin(); i != BorderItems.end();) {
				if (Path::IsArea(*i)) {
					for (auto c = 0; c < 20; c++) {
						d = { i->x + closer[c].x, i->y + closer[c].y };
						if (Path::inWindow(d)) {
							if (graph(d)->isArea) {
								if (!graph(d)->isInside) {
									for (auto j = 0; j < 8; j++) {
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
				}
				else {
					++i;
				}
			}
			if (InsideItems.size() > 0) {
				GraphItems.clear();
				for (auto i = 0; i < InsideItems.size(); i++) {
					graph(InsideItems[i])->isInside = false;
					GraphItems.insert(GraphItems.end(), graph(InsideItems[i]));
				}
				InsideItems.clear();
			}
			Find(Area.sc);
		}

		if (changed || Area.p != Enter) {
			Area.p = Enter;
			Field *Game = Field::getInstance();
			Cell *current = &Game->cells[Point.x][Point.y];
			if (graph(Point)->isArea) {
				/*int min = 0, p = -1;
				for (int c = 0; c < 8; c++){
					if (graph(Point)->Out[c] >= 0 && graph(Point)->f[c] && graph(Point)->d[c] > 0 && (min == 0 || graph(Point)->d[c] < min)){
						min = graph(Point)->d[c];
						p = c;
					}
				}
				*/
				int p = -1;
				if (graph(Point)->Out[Enter] >= 0 && graph(Point)->f[Enter] && graph(Point)->d[Enter] > 0) {
					p = Enter;
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
		} //changed
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
			for (int c = 0; c < 8; c++) {
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
				if (!graph(p)->isBorder /*&& (element == Horizontal || element == Vertical || element == Item45 || element == Item135)*/){
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
			//CCLOG("m %.2f,%.2f|%.2f,%.2f|%d,%d|%d,%d|", m.x, m.y, Area.sin, Area.cos, Area.s.x, Area.s.y, Point.x, Point.y);
			if (m.x > -Area.Width && m.x < Area.Width + Area.dt && m.y > -Area.Width && m.y < Area.Width) {
				
				//debug
				//debugNode->drawDot({ (float)(Point.x * 20), (float)(Point.y * 20) }, 2.0, Color4F::BLUE);

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

	Vec2 Path::GetPosition(TrackPosition position)
	{
		Vec2 p = {0, 0};
		int s = Field::getInstance()->scale;

		int indent;
		Entry *entry;
		Cell *cell = position.cell;

		if (position.indent > 0) {
			entry = position.cell->getEntry(position.point);
			if (entry->Enter == 0) {
				indent = position.indent;
				p = track[entry->Element].items[indent] * s;
			} else {
				cell = entry->to;
				entry = entry->to->getEntry(entry->Point);
				indent = track[entry->Element].items.size() - position.indent;
				if (indent > 0) {
					p = track[entry->Element].items[indent] * s;
				}
			}
		}
		return { cell->x * 10 * s + p.x,  cell->y * 10 * s + p.y };
	}

	TrackPosition Path::GetPosition(TrackPosition position, int increase)
	{
		TrackPosition pos = position;
		int i = increase > 0 ? increase : -increase;

		while (i > 0) {
			if (increase > 0) {
				Entry *entry = pos.cell->getEntry(pos.point);
				int TrackLength = track[entry->Element].items.size();
				if (pos.indent + i < TrackLength) {
					pos.indent = pos.indent + i;
					i = 0;
				}
				if (pos.indent + i >= TrackLength) {
					int nextPoint = Cell::Related[entry->Point];
					if (entry->to->getEntry(nextPoint) != 0) {
						i = i - TrackLength + pos.indent;
						pos.cell = entry->to;
						pos.indent = 0;
						pos.point = nextPoint;
					} else {
						pos.indent = TrackLength - i;
						i = 0;
					}
				}
			} else {
				if (pos.indent - i >= 0) {
					pos.indent = pos.indent - i;
					i = 0;
				}
				if (pos.indent - i < 0) {
					int nextPoint = Cell::Related[pos.point];
					if (pos.cell->getEntry(nextPoint) != 0) {
						i = i - (pos.indent + 1);
						Entry *entry = pos.cell->getEntry(nextPoint);
						pos.cell = entry->to;
						pos.point = entry->Point;
						pos.indent = track[entry->Element].items.size() - 1;
					} else {
						pos.indent = 0;
						i = 0;
					}
				}
			}
		}		
		return pos;
	}
}
