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

	const TrackItem Path::track[24] = {
		{ 0,{ { 0, -1 },{ 0, 1 } },{ 6, 2 },{ SwitchElement::Vertical0 , SwitchElement::Vertical1 }, { 2, 2, 1, 2, 2, 2, 0, 2 },10,{ { 0, 0 }, { 0, -1 },{ 0, -2 },{ 0, -3 },{ 0, -4 },{ 0, -5 },{ 0, -6 },{ 0, -7 },{ 0, -8 },{ 0, -9 } } },
		{ 0,{ { 1, 0 },{ -1, 0 } },{ 0, 4 },{ SwitchElement::Horizontal0 , SwitchElement::Horizontal1 },{ 0, 2, 2, 2, 1, 2, 2, 2 },10,{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 3, 0 },{ 4, 0 },{ 5, 0 },{ 6, 0 },{ 7, 0 },{ 8, 0 },{ 9, 0 } } },
		{ 0,{ { 1, 1 },{ -1, -1 } },{ 1, 5 },{ SwitchElement::Item450 , SwitchElement::Item451 },{ 2, 0, 2, 2, 2, 1, 2, 2 },14,{ { 0, 0 },{ 0.71f, 0.71f },{ 1.41f, 1.41f },{ 2.12f, 2.12f },{ 2.83f, 2.83f },{ 3.54f, 3.54f },{ 4.24f, 4.24f },{ 4.95f, 4.95f },{ 5.66f, 5.66f },{ 6.36f, 6.36f },{ 7.07f, 7.07f },{ 7.78f, 7.78f },{ 8.49f, 8.49f },{ 9.19f, 9.19f } } },
		{ 0,{ { 1, -1 },{ -1, 1 } },{ 7, 3 },{ SwitchElement::Item1350 , SwitchElement::Item1351 },{ 2, 2, 2, 1, 2, 2, 2, 0 },14,{ { 0, 0 },{ 0.71f, -0.71f },{ 1.41f, -1.41f },{ 2.12f, -2.12f },{ 2.83f, -2.83f },{ 3.54f, -3.54f },{ 4.24f, -4.24f },{ 4.95f, -4.95f },{ 5.66f, -5.66f },{ 6.36f, -6.36f },{ 7.07f, -7.07f },{ 7.78f, -7.78f },{ 8.49f, -8.49f },{ 9.19f, -9.19f } } },
		//13
		{ 10,{ { -1, 3 },{ 1, -3 } },{ 2, 7 },{ SwitchElement::BaseCircleSect00 , SwitchElement::BaseCircleSect01 },{ 2, 2, 0, 2, 2, 2, 2, 1 },32,{ { 0, 0 },{ -0.01f, 1 },{ -0.04f, 2 },{ -0.09f, 3 },{ -0.16f, 4 },{ -0.25f, 4.99f },{ -0.36f, 5.99f },{ -0.49f, 6.98f },{ -0.64f, 7.97f },{ -0.81f, 8.95f },{ -1, 9.93f },{ -1.21f, 10.91f },{ -1.43f, 11.89f },{ -1.68f, 12.85f },{ -1.95f, 13.82f },{ -2.23f, 14.78f },{ -2.54f, 15.73f },{ -2.86f, 16.67f },{ -3.21f, 17.61f },{ -3.57f, 18.55f },{ -3.95f, 19.47f },{ -4.35f, 20.39f },{ -4.76f, 21.3f },{ -5.2f, 22.2f },{ -5.65f, 23.09f },{ -6.12f, 23.97f },{ -6.61f, 24.84f },{ -7.11f, 25.71f },{ -7.64f, 26.56f },{ -8.18f, 27.4f },{ -8.73f, 28.23f },{ -9.31f, 29.05f } } },
		{ 10,{ { -3, 1 },{ 3, -1 } },{ 3, 0 },{ SwitchElement::BaseCircleSect10 , SwitchElement::BaseCircleSect11 },{ 1, 2, 2, 0, 2, 2, 2, 2 },32,{ { 0, 0 },{ -0.81f, 0.59f },{ -1.62f, 1.17f },{ -2.45f, 1.73f },{ -3.29f, 2.27f },{ -4.14f, 2.8f },{ -5, 3.3f },{ -5.88f, 3.79f },{ -6.76f, 4.27f },{ -7.65f, 4.72f },{ -8.54f, 5.16f },{ -9.45f, 5.58f },{ -10.37f, 5.98f },{ -11.29f, 6.37f },{ -12.22f, 6.73f },{ -13.16f, 7.08f },{ -14.11f, 7.41f },{ -15.06f, 7.71f },{ -16.01f, 8 },{ -16.98f, 8.27f },{ -17.95f, 8.52f },{ -18.92f, 8.76f },{ -19.9f, 8.97f },{ -20.88f, 9.16f },{ -21.86f, 9.33f },{ -22.85f, 9.49f },{ -23.84f, 9.62f },{ -24.83f, 9.73f },{ -25.83f, 9.83f },{ -26.83f, 9.9f },{ -27.83f, 9.95f },{ -28.83f, 9.99f } } },
		{ 10,{ { -3, -1 },{ 3, 1 } },{ 4, 1 },{ SwitchElement::BaseCircleSect20 , SwitchElement::BaseCircleSect21 },{ 2, 1, 2, 2, 0, 2, 2, 2 },32,{ { 0, 0 },{ -1, -0.01f },{ -2, -0.04f },{ -3, -0.09f },{ -4, -0.16f },{ -4.99f, -0.25f },{ -5.99f, -0.36f },{ -6.98f, -0.49f },{ -7.97f, -0.64f },{ -8.95f, -0.81f },{ -9.93f, -1 },{ -10.91f, -1.21f },{ -11.89f, -1.43f },{ -12.85f, -1.68f },{ -13.82f, -1.95f },{ -14.78f, -2.23f },{ -15.73f, -2.54f },{ -16.67f, -2.86f },{ -17.61f, -3.21f },{ -18.55f, -3.57f },{ -19.47f, -3.95f },{ -20.39f, -4.35f },{ -21.3f, -4.76f },{ -22.2f, -5.2f },{ -23.09f, -5.65f },{ -23.97f, -6.12f },{ -24.84f, -6.61f },{ -25.71f, -7.11f },{ -26.56f, -7.64f },{ -27.4f, -8.18f },{ -28.23f, -8.73f },{ -29.05f, -9.31f } } },
		{ 10,{ { -1, -3 },{ 1, 3 } },{ 5, 2 },{ SwitchElement::BaseCircleSect30 , SwitchElement::BaseCircleSect31 },{ 2, 2, 1, 2, 2, 0, 2, 2 },32,{ { 0, 0 },{ -0.59f, -0.81f },{ -1.17f, -1.62f },{ -1.73f, -2.45f },{ -2.27f, -3.29f },{ -2.8f, -4.14f },{ -3.3f, -5 },{ -3.79f, -5.88f },{ -4.27f, -6.76f },{ -4.72f, -7.65f },{ -5.16f, -8.54f },{ -5.58f, -9.45f },{ -5.98f, -10.37f },{ -6.37f, -11.29f },{ -6.73f, -12.22f },{ -7.08f, -13.16f },{ -7.41f, -14.11f },{ -7.71f, -15.06f },{ -8, -16.01f },{ -8.27f, -16.98f },{ -8.52f, -17.95f },{ -8.76f, -18.92f },{ -8.97f, -19.9f },{ -9.16f, -20.88f },{ -9.33f, -21.86f },{ -9.49f, -22.85f },{ -9.62f, -23.84f },{ -9.73f, -24.83f },{ -9.83f, -25.83f },{ -9.9f, -26.83f },{ -9.95f, -27.83f },{ -9.99f, -28.83f } } },
		{ 10,{ { 1, -3 },{ -1, 3 } },{ 6, 3 },{ SwitchElement::BaseCircleSect40 , SwitchElement::BaseCircleSect41 },{ 2, 2, 2, 1, 2, 2, 0, 2 },32,{ { 0, 0 },{ 0.01f, -1 },{ 0.04f, -2 },{ 0.09f, -3 },{ 0.16f, -4 },{ 0.25f, -4.99f },{ 0.36f, -5.99f },{ 0.49f, -6.98f },{ 0.64f, -7.97f },{ 0.81f, -8.95f },{ 1, -9.93f },{ 1.21f, -10.91f },{ 1.43f, -11.89f },{ 1.68f, -12.85f },{ 1.95f, -13.82f },{ 2.23f, -14.78f },{ 2.54f, -15.73f },{ 2.86f, -16.67f },{ 3.21f, -17.61f },{ 3.57f, -18.55f },{ 3.95f, -19.47f },{ 4.35f, -20.39f },{ 4.76f, -21.3f },{ 5.2f, -22.2f },{ 5.65f, -23.09f },{ 6.12f, -23.97f },{ 6.61f, -24.84f },{ 7.11f, -25.71f },{ 7.64f, -26.56f },{ 8.18f, -27.4f },{ 8.73f, -28.23f },{ 9.31f, -29.05f } } },
		{ 10,{ { 3, -1 },{ -3, 1 } },{ 7, 4 },{ SwitchElement::BaseCircleSect50 , SwitchElement::BaseCircleSect51 },{ 2, 2, 2, 2, 1, 2, 2, 0 },32,{ { 0, 0 },{ 0.81f, -0.59f },{ 1.62f, -1.17f },{ 2.45f, -1.73f },{ 3.29f, -2.27f },{ 4.14f, -2.8f },{ 5, -3.3f },{ 5.88f, -3.79f },{ 6.76f, -4.27f },{ 7.65f, -4.72f },{ 8.54f, -5.16f },{ 9.45f, -5.58f },{ 10.37f, -5.98f },{ 11.29f, -6.37f },{ 12.22f, -6.73f },{ 13.16f, -7.08f },{ 14.11f, -7.41f },{ 15.06f, -7.71f },{ 16.01f, -8 },{ 16.98f, -8.27f },{ 17.95f, -8.52f },{ 18.92f, -8.76f },{ 19.9f, -8.97f },{ 20.88f, -9.16f },{ 21.86f, -9.33f },{ 22.85f, -9.49f },{ 23.84f, -9.62f },{ 24.83f, -9.73f },{ 25.83f, -9.83f },{ 26.83f, -9.9f },{ 27.83f, -9.95f },{ 28.83f, -9.99f } } },
		{ 10,{ { 3, 1 },{ -3, -1 } },{ 0, 5 },{ SwitchElement::BaseCircleSect60 , SwitchElement::BaseCircleSect61 },{ 0, 2, 2, 2, 2, 1, 2, 2 },32,{ { 0, 0 },{ 1, 0.01f },{ 2, 0.04f },{ 3, 0.09f },{ 4, 0.16f },{ 4.99f, 0.25f },{ 5.99f, 0.36f },{ 6.98f, 0.49f },{ 7.97f, 0.64f },{ 8.95f, 0.81f },{ 9.93f, 1 },{ 10.91f, 1.21f },{ 11.89f, 1.43f },{ 12.85f, 1.68f },{ 13.82f, 1.95f },{ 14.78f, 2.23f },{ 15.73f, 2.54f },{ 16.67f, 2.86f },{ 17.61f, 3.21f },{ 18.55f, 3.57f },{ 19.47f, 3.95f },{ 20.39f, 4.35f },{ 21.3f, 4.76f },{ 22.2f, 5.2f },{ 23.09f, 5.65f },{ 23.97f, 6.12f },{ 24.84f, 6.61f },{ 25.71f, 7.11f },{ 26.56f, 7.64f },{ 27.4f, 8.18f },{ 28.23f, 8.73f },{ 29.05f, 9.31f } } },
		{ 10,{ { 1, 3 },{ -1, -3 } },{ 1, 6 },{ SwitchElement::BaseCircleSect70 , SwitchElement::BaseCircleSect71 },{ 2, 0, 2, 2, 2, 2, 1, 2 },32,{ { 0, 0 },{ 0.59f, 0.81f },{ 1.17f, 1.62f },{ 1.73f, 2.45f },{ 2.27f, 3.29f },{ 2.8f, 4.14f },{ 3.3f, 5 },{ 3.79f, 5.88f },{ 4.27f, 6.76f },{ 4.72f, 7.65f },{ 5.16f, 8.54f },{ 5.58f, 9.45f },{ 5.98f, 10.37f },{ 6.37f, 11.29f },{ 6.73f, 12.22f },{ 7.08f, 13.16f },{ 7.41f, 14.11f },{ 7.71f, 15.06f },{ 8, 16.01f },{ 8.27f, 16.98f },{ 8.52f, 17.95f },{ 8.76f, 18.92f },{ 8.97f, 19.9f },{ 9.16f, 20.88f },{ 9.33f, 21.86f },{ 9.49f, 22.85f },{ 9.62f, 23.84f },{ 9.73f, 24.83f },{ 9.83f, 25.83f },{ 9.9f, 26.83f },{ 9.95f, 27.83f },{ 9.99f, 28.83f } } },
		//10
		{ 7,{ { -2, 2 },{ 2, -2 } },{ 2, 0 },{ SwitchElement::SmallCilcleSect00 , SwitchElement::SmallCilcleSect01 },{ 1, 2, 0, 2, 2, 2, 2, 2 },31,{ { 0, 0 },{ -0.02f, 1 },{ -0.1f, 2 },{ -0.22f, 2.99f },{ -0.4f, 3.97f },{ -0.62f, 4.95f },{ -0.89f, 5.91f },{ -1.21f, 6.86f },{ -1.58f, 7.79f },{ -1.99f, 8.7f },{ -2.45f, 9.59f },{ -2.95f, 10.45f },{ -3.49f, 11.29f },{ -4.08f, 12.1f },{ -4.7f, 12.88f },{ -5.37f, 13.63f },{ -6.07f, 14.35f },{ -6.8f, 15.03f },{ -7.57f, 15.67f },{ -8.37f, 16.27f },{ -9.19f, 16.83f },{ -10.05f, 17.35f },{ -10.93f, 17.82f },{ -11.83f, 18.26f },{ -12.75f, 18.64f },{ -13.69f, 18.98f },{ -14.65f, 19.27f },{ -15.62f, 19.51f },{ -16.6f, 19.71f },{ -17.59f, 19.85f },{ -18.59f, 19.95f } } },
		{ 7,{ { -2, -2 },{ 2, 2 } },{ 4, 2 },{ SwitchElement::SmallCilcleSect10 , SwitchElement::SmallCilcleSect11 },{ 2, 2, 1, 2, 0, 2, 2, 2 },31,{ { 0, 0 },{ -1, -0.02f },{ -2, -0.1f },{ -2.99f, -0.22f },{ -3.97f, -0.4f },{ -4.95f, -0.62f },{ -5.91f, -0.89f },{ -6.86f, -1.21f },{ -7.79f, -1.58f },{ -8.7f, -1.99f },{ -9.59f, -2.45f },{ -10.45f, -2.95f },{ -11.29f, -3.49f },{ -12.1f, -4.08f },{ -12.88f, -4.7f },{ -13.63f, -5.37f },{ -14.35f, -6.07f },{ -15.03f, -6.8f },{ -15.67f, -7.57f },{ -16.27f, -8.37f },{ -16.83f, -9.19f },{ -17.35f, -10.05f },{ -17.82f, -10.93f },{ -18.26f, -11.83f },{ -18.64f, -12.75f },{ -18.98f, -13.69f },{ -19.27f, -14.65f },{ -19.51f, -15.62f },{ -19.71f, -16.6f },{ -19.85f, -17.59f },{ -19.95f, -18.59f } } },
		{ 7,{ { 2, -2 },{ -2, 2 } },{ 6, 4 },{ SwitchElement::SmallCilcleSect20 , SwitchElement::SmallCilcleSect21 },{ 2, 2, 2, 2, 1, 2, 0, 2 },31,{ { 0, 0 },{ 0.02f, -1 },{ 0.1f, -2 },{ 0.22f, -2.99f },{ 0.4f, -3.97f },{ 0.62f, -4.95f },{ 0.89f, -5.91f },{ 1.21f, -6.86f },{ 1.58f, -7.79f },{ 1.99f, -8.7f },{ 2.45f, -9.59f },{ 2.95f, -10.45f },{ 3.49f, -11.29f },{ 4.08f, -12.1f },{ 4.7f, -12.88f },{ 5.37f, -13.63f },{ 6.07f, -14.35f },{ 6.8f, -15.03f },{ 7.57f, -15.67f },{ 8.37f, -16.27f },{ 9.19f, -16.83f },{ 10.05f, -17.35f },{ 10.93f, -17.82f },{ 11.83f, -18.26f },{ 12.75f, -18.64f },{ 13.69f, -18.98f },{ 14.65f, -19.27f },{ 15.62f, -19.51f },{ 16.6f, -19.71f },{ 17.59f, -19.85f },{ 18.59f, -19.95f } } },
		{ 7,{ { 2, 2 },{ -2, -2 } },{ 0, 6 },{ SwitchElement::SmallCilcleSect30 , SwitchElement::SmallCilcleSect31 },{ 0, 2, 2, 2, 2, 2, 1, 2 },31,{ { 0, 0 },{ 1, 0.02f },{ 2, 0.1f },{ 2.99f, 0.22f },{ 3.97f, 0.4f },{ 4.95f, 0.62f },{ 5.91f, 0.89f },{ 6.86f, 1.21f },{ 7.79f, 1.58f },{ 8.7f, 1.99f },{ 9.59f, 2.45f },{ 10.45f, 2.95f },{ 11.29f, 3.49f },{ 12.1f, 4.08f },{ 12.88f, 4.7f },{ 13.63f, 5.37f },{ 14.35f, 6.07f },{ 15.03f, 6.8f },{ 15.67f, 7.57f },{ 16.27f, 8.37f },{ 16.83f, 9.19f },{ 17.35f, 10.05f },{ 17.82f, 10.93f },{ 18.26f, 11.83f },{ 18.64f, 12.75f },{ 18.98f, 13.69f },{ 19.27f, 14.65f },{ 19.51f, 15.62f },{ 19.71f, 16.6f },{ 19.85f, 17.59f },{ 19.95f, 18.59f } } },
		
		// 5
		{ 5,{ { 3, -1 },{ -3, 1 } },{ 0, 4 },{ SwitchElement::Crossover000 , SwitchElement::Crossover001 }, { 0, 2, 2, 2, 1, 2, 2, 2 },32,{ { 1, -0.02f },{ 2, -0.08f },{ 2.99f, -0.18f },{ 3.98f, -0.32f },{ 4.97f, -0.5f },{ 5.94f, -0.72f },{ 6.91f, -0.97f },{ 7.86f, -1.27f },{ 8.81f, -1.6f },{ 9.74f, -1.97f },{ 10.65f, -2.38f },{ 11.54f, -2.83f },{ 12.42f, -3.3f },{ 13.28f, -3.82f },{ 14.12f, -4.37f },{ 14.93f, -4.95f },{ 15.74f, -5.54f },{ 16.57f, -6.09f },{ 17.43f, -6.61f },{ 18.3f, -7.09f },{ 19.2f, -7.54f },{ 20.11f, -7.95f },{ 21.03f, -8.33f },{ 21.97f, -8.67f },{ 22.93f, -8.97f },{ 23.89f, -9.23f },{ 24.87f, -9.46f },{ 25.85f, -9.64f },{ 26.84f, -9.79f },{ 27.83f, -9.89f },{ 28.83f, -9.96f },{ 29.83f, -9.98f } } },
		{ 5,{ { 3, 1 },{ -3, -1 } },{ 0, 4 },{ SwitchElement::Crossover010 , SwitchElement::Crossover011 }, { 0, 2, 2, 2, 1, 2, 2, 2 },32,{ { 1, 0.02f },{ 2, 0.08f },{ 2.99f, 0.18f },{ 3.98f, 0.32f },{ 4.97f, 0.5f },{ 5.94f, 0.72f },{ 6.91f, 0.97f },{ 7.86f, 1.27f },{ 8.81f, 1.6f },{ 9.74f, 1.97f },{ 10.65f, 2.38f },{ 11.54f, 2.83f },{ 12.42f, 3.3f },{ 13.28f, 3.82f },{ 14.12f, 4.37f },{ 14.93f, 4.95f },{ 15.74f, 5.54f },{ 16.57f, 6.09f },{ 17.43f, 6.61f },{ 18.3f, 7.09f },{ 19.2f, 7.54f },{ 20.11f, 7.95f },{ 21.03f, 8.33f },{ 21.97f, 8.67f },{ 22.93f, 8.97f },{ 23.89f, 9.23f },{ 24.87f, 9.46f },{ 25.85f, 9.64f },{ 26.84f, 9.79f },{ 27.83f, 9.89f },{ 28.83f, 9.96f },{ 29.83f, 9.98f } } },
		{ 5,{ { 2, 1 },{ -2, -1 } },{ 1, 5 },{ SwitchElement::Crossover100 , SwitchElement::Crossover101 }, { 2, 0, 2, 2, 2, 1, 2, 2 },22,{ { 0.81f, 0.59f },{ 1.64f, 1.15f },{ 2.48f, 1.68f },{ 3.35f, 2.19f },{ 4.22f, 2.67f },{ 5.12f, 3.11f },{ 6.02f, 3.53f },{ 6.95f, 3.93f },{ 7.88f, 4.29f },{ 8.82f, 4.62f },{ 9.78f, 4.92f },{ 10.74f, 5.21f },{ 11.68f, 5.53f },{ 12.62f, 5.88f },{ 13.55f, 6.26f },{ 14.46f, 6.67f },{ 15.36f, 7.11f },{ 16.24f, 7.57f },{ 17.11f, 8.07f },{ 17.96f, 8.59f },{ 18.8f, 9.15f },{ 19.61f, 9.72f } } },
		{ 5,{ { 1, 2 },{ -1, -2 } },{ 1, 5 },{ SwitchElement::Crossover110 , SwitchElement::Crossover111 }, { 2, 0, 2, 2, 2, 1, 2, 2 },22,{ { 0.59f, 0.81f },{ 1.15f, 1.64f },{ 1.68f, 2.48f },{ 2.19f, 3.35f },{ 2.67f, 4.22f },{ 3.11f, 5.12f },{ 3.53f, 6.02f },{ 3.93f, 6.95f },{ 4.29f, 7.88f },{ 4.62f, 8.82f },{ 4.92f, 9.78f },{ 5.21f, 10.74f },{ 5.53f, 11.68f },{ 5.88f, 12.62f },{ 6.26f, 13.55f },{ 6.67f, 14.46f },{ 7.11f, 15.36f },{ 7.57f, 16.24f },{ 8.07f, 17.11f },{ 8.59f, 17.96f },{ 9.15f, 18.8f },{ 9.72f, 19.61f } } },
		{ 5,{ { 1, 3 },{ -1, -3 } },{ 2, 6 },{ SwitchElement::Crossover200 , SwitchElement::Crossover201 }, { 2, 2, 0, 2, 2, 2, 1, 2 },32,{ { 0.02f, 1 },{ 0.08f, 2 },{ 0.18f, 2.99f },{ 0.32f, 3.98f },{ 0.5f, 4.97f },{ 0.72f, 5.94f },{ 0.97f, 6.91f },{ 1.27f, 7.86f },{ 1.6f, 8.81f },{ 1.97f, 9.74f },{ 2.38f, 10.65f },{ 2.83f, 11.54f },{ 3.3f, 12.42f },{ 3.82f, 13.28f },{ 4.37f, 14.12f },{ 4.95f, 14.93f },{ 5.54f, 15.74f },{ 6.09f, 16.57f },{ 6.61f, 17.43f },{ 7.09f, 18.3f },{ 7.54f, 19.2f },{ 7.95f, 20.11f },{ 8.33f, 21.03f },{ 8.67f, 21.97f },{ 8.97f, 22.93f },{ 9.23f, 23.89f },{ 9.46f, 24.87f },{ 9.64f, 25.85f },{ 9.79f, 26.84f },{ 9.89f, 27.83f },{ 9.96f, 28.83f },{ 9.98f, 29.83f } } },
		{ 5,{ { -1, 3 },{ 1, -3 } },{ 2, 6 },{ SwitchElement::Crossover210 , SwitchElement::Crossover211 }, { 2, 2, 0, 2, 2, 2, 1, 2 },32,{ { -0.02f, 1 },{ -0.08f, 2 },{ -0.18f, 2.99f },{ -0.32f, 3.98f },{ -0.5f, 4.97f },{ -0.72f, 5.94f },{ -0.97f, 6.91f },{ -1.27f, 7.86f },{ -1.6f, 8.81f },{ -1.97f, 9.74f },{ -2.38f, 10.65f },{ -2.83f, 11.54f },{ -3.3f, 12.42f },{ -3.82f, 13.28f },{ -4.37f, 14.12f },{ -4.95f, 14.93f },{ -5.54f, 15.74f },{ -6.09f, 16.57f },{ -6.61f, 17.43f },{ -7.09f, 18.3f },{ -7.54f, 19.2f },{ -7.95f, 20.11f },{ -8.33f, 21.03f },{ -8.67f, 21.97f },{ -8.97f, 22.93f },{ -9.23f, 23.89f },{ -9.46f, 24.87f },{ -9.64f, 25.85f },{ -9.79f, 26.84f },{ -9.89f, 27.83f },{ -9.96f, 28.83f },{ -9.98f, 29.83f } } },
		{ 5,{ { -1, 2 },{ 1, -2 } },{ 3, 7 },{ SwitchElement::Crossover300 , SwitchElement::Crossover301 }, { 2, 2, 2, 0, 2, 2, 2, 1 },22,{ { -0.29f, 0.96f },{ -0.61f, 1.9f },{ -0.96f, 2.84f },{ -1.34f, 3.77f },{ -1.75f, 4.68f },{ -2.19f, 5.58f },{ -2.65f, 6.46f },{ -3.15f, 7.33f },{ -3.67f, 8.18f },{ -4.23f, 9.02f },{ -4.8f, 9.83f },{ -5.39f, 10.64f },{ -5.95f, 11.47f },{ -6.48f, 12.31f },{ -6.99f, 13.18f },{ -7.47f, 14.05f },{ -7.91f, 14.95f },{ -8.33f, 15.85f },{ -8.73f, 16.78f },{ -9.09f, 17.71f },{ -9.42f, 18.65f },{ -9.72f, 19.61f } } },
		{ 5,{ { -2, 1 },{ 2, -1 } },{ 3, 7 },{ SwitchElement::Crossover310 , SwitchElement::Crossover311 }, { 2, 2, 2, 0, 2, 2, 2, 1 },22,{ { -0.81f, 0.59f },{ -1.64f, 1.15f },{ -2.48f, 1.68f },{ -3.35f, 2.19f },{ -4.22f, 2.67f },{ -5.12f, 3.11f },{ -6.02f, 3.53f },{ -6.95f, 3.93f },{ -7.88f, 4.29f },{ -8.82f, 4.62f },{ -9.78f, 4.92f },{ -10.74f, 5.21f },{ -11.68f, 5.53f },{ -12.62f, 5.88f },{ -13.55f, 6.26f },{ -14.46f, 6.67f },{ -15.36f, 7.11f },{ -16.24f, 7.57f },{ -17.11f, 8.07f },{ -17.96f, 8.59f },{ -18.8f, 9.15f },{ -19.61f, 9.72f } } },
	};
	
	const AccessItems Path::access[2][24] = {
		{
			//{},{},{},{},
			{ { { 0b11000001,0b0,{ 0, -1 } } } },
			{ { { 0b00000111,0b0,{ 0, 0 } } } },
			{ { { 0b00010001,0b1,{ 0, 0 } } } },
			{ { { 0b01000100,0b1,{ 0, -1 } } } },
			
			
			// base circle	
			//{},{},{},{},{},{},{},{},
			{ { { 0b00010000,0b0,{ -1, 0 } },{ 0b00011100,0b0,{ -1, 1 } },{ 0b01000110,0b1,{ -1, 2 } },{ 0b11000001,0b0,{ 0, 0 } } } },
			{ { { 0b01100100,0b1,{ -1, 0 } },{ 0b01110000,0b0,{ -2, 0 } },{ 0b00010000,0b0,{ -3, 0 } },{ 0b00000111,0b0,{ -3, 1 } } } },
			{ { { 0b01000000,0b0,{ -1, -1 } },{ 0b01110000,0b0,{ -2, -1 } },{ 0b00011001,0b1,{ -3, -1 } },{ 0b00000111,0b0,{ -1, 0 } } } },
			{ { { 0b00010010,0b1,{ -1, -1 } },{ 0b00100010,0b1,{ -1, -2 } },{ 0b11100001,0b0,{ -1, -3 } } } },
			{ { { 0b11000011,0b0,{ 0, -1 } },{ 0b00100010,0b1,{ 0, -2 } },{ 0b00100100,0b1,{ 0, -3 } } } },
			{ { { 0b01001000,0b1,{ 0, -1 } },{ 0b10001000,0b1,{ 1, -1 } },{ 0b10000111,0b0,{ 2, -1 } } } },
			{ { { 0b00001111,0b0,{ 0, 0 } },{ 0b10001000,0b1,{ 1, 0 } },{ 0b10010000,0b1,{ 2, 0 } } } },
			{ { { 0b00110001,0b1,{ 0, 0 } },{ 0b00011100,0b0,{ 0, 1 } },{ 0b00000100,0b0,{ 0, 2 } },{ 0b11000001,0b0,{ 1, 2 } } } },

			// small circle
			//{},{},{},{},
			{ { { 0b00010000,0b0,{ -1, 0 } },{ 0b01000100,0b1,{ -1, 1 } },{ 0b00010000,0b0,{ -2, 1 } },{ 0b11000001,0b0,{ 0, 0 } }, { 0b00000111,0b0,{ -2, 2 } } } },
			{ { { 0b01000000,0b0,{ -1, -1 } },{ 0b00010010,0b1,{ -2, -1 } },{ 0b11100001,0b0,{ -2, -2 } },{ 0b00000111,0b0,{ -1, 0 } } } },
			{ { { 0b11000011,0b0,{ 0, -1 } },{ 0b00101000,0b1,{ 0, -2 } },{ 0b10000111,0b0,{ 1, -2 } } } },
			{ { { 0b00001111,0b0,{ 0, 0 } },{ 0b10010000,0b1,{ 1, 0 } },{ 0b00000100,0b0,{ 1, 1 } },{ 0b11000001,0b0,{ 2, 1 } } } },
			
			// crossover
			{ { { 0b000000011,0b0,{ 0, 0 } },{ 0b00010000,0b0,{ 0, -1 } },{ 0b01101000,0b1,{ 1, -1 } },{ 0b10000110,0b0,{ 2, -1 } } } },		
			{ { { 0b000001011,0b0,{ 0, 0 } },{ 0b10110000,0b1,{ 1, 0 } },{ 0b01000000,0b0,{ 2, 0 } },{ 0b00000110,0b0,{ 2, 1 } } } },

			{ { { 0b00001001,0b1,{ 0, 0 } },{ 0b10010000,0b1,{ 1, 0 } } } },
			{ { { 0b00100001,0b1,{ 0, 0 } },{ 0b00010010,0b1,{ 0, 1 } } } },

			{ { { 0b10100001,0b0,{ 0, 0 } },{ 0b00011010,0b1,{ 0, 1 } },{ 0b00000100,0b0,{ 0, 2 } },{ 0b11000000,0b0,{ 1, 2 } } } },
			{ { { 0b10000001,0b0,{ 0, 0 } },{ 0b00010000,0b0,{ -1, 0 } },{ 0b00101100,0b1,{ -1, 1 } },{ 0b11000010,0b0,{ -1, 2 } } } },

			{ { { 0b00100100,0b1,{ -1, 0 } },{ 0b01000010,0b1,{ -1, 1 } } } },
			{ { { 0b10000100,0b1,{ -1, 0 } },{ 0b01001000,0b1,{ -2, 0 } } } },
		},{
			//{},{},{},{},
			{ { { 0b11000001,0b0,{ 0, 0 } } } },
			{ { { 0b00000111,0b0,{ -1, 0 } } } },
			{ { { 0b00010001,0b1,{ -1, -1 } } } },
			{ { { 0b01000100,0b1,{ -1, 0 } } } },

			// base circle
			//{},{},{},{},{},{},{},{},
			{ { { 0b00010000,0b0,{0, -3 } },{ 0b00011100,0b0,{ 0, -2 } },{ 0b01000110,0b1,{ 0, -1 } },{ 0b11000001,0b0,{ 1, -3 } } } },
			{ { { 0b01100100,0b1,{ 2, -1 } },{ 0b01110000,0b0,{ 1, -1 } },{ 0b00010000,0b0,{ 0, -1 } },{ 0b00000111,0b0,{ 0, 0 } } } },
			{ { { 0b01000000,0b0,{ 2, 0 } },{ 0b01110000,0b0,{ 1, 0 } },{ 0b00011001,0b1,{ 0, 0 } },{ 0b00000111,0b0,{ 2, 1 } } } },
			{ { { 0b00010010,0b1,{ 0, 2 } },{ 0b00100010,0b1,{ 0, 1 } },{ 0b11100001,0b0,{ 0, 0 } } } },
			{ { { 0b11000011,0b0,{ -1, 2 } },{ 0b00100010,0b1,{ -1, 1 } },{ 0b00100100,0b1,{ -1, 0 } } } },
			{ { { 0b01001000,0b1,{ -3, 0 } },{ 0b10001000,0b1,{ -2, 0 } },{ 0b10000111,0b0,{ -1, 0 } } } },
			{ { { 0b00001111,0b0,{ -3, -1 } },{ 0b10001000,0b1,{ -2, -1 } },{ 0b10010000,0b1,{ -1, -1 } } } },
			{ { { 0b00110001,0b1,{ -1, -3 } },{ 0b00011100,0b0,{ -1, -2 } },{ 0b00000100,0b0,{ -1, -1 } },{ 0b11000001,0b0,{ 0, -1 } } } },

			// small circle
			//{},{},{},{},
			{ { { 0b00010000,0b0,{ 1, -2 } },{ 0b01000100,0b1,{ 1, -1 } },{ 0b00010000,0b0,{ 0, -1 } },{ 0b11000001,0b0,{ 2, -2 } },{ 0b00000111,0b0,{ 0, 0 } } } },
			{ { { 0b01000000,0b0,{ 1, 1 } },{ 0b00010010,0b1,{ 0, 1 } },{ 0b11100001,0b0,{ 0, 0 } },{ 0b00000111,0b0,{ 1, 2 } } } },
			{ { { 0b11000011,0b0,{ -2, 1 } },{ 0b00101000,0b1,{ -2, 0 } },{ 0b10000111,0b0,{ -1, 0 } } } },
			{ { { 0b00001111,0b0,{ -2, -2 } },{ 0b10010000,0b1,{ -1, -2 } },{ 0b00000100,0b0,{ -1, -1 } },{ 0b11000001,0b0,{ 0, -1 } } } },

			// crossover
			{ { { 0b000000011,0b0,{ -3, 1 } },{ 0b00010000,0b0,{ -3, 0 } },{ 0b01101000,0b1,{ -2, 0 } },{ 0b10000110,0b0,{ -1, 0 } } } },
			{ { { 0b000001011,0b0,{ -3, -1 } },{ 0b10110000,0b1,{ -2, -1 } },{ 0b01000000,0b0,{ -1, -1 } },{ 0b00000110,0b0,{ -1, 0 } } } },

			{ { { 0b00001001,0b1,{ -2, -1 } },{ 0b10010000,0b1,{ -1, -1 } } } },
			{ { { 0b00100001,0b1,{ -1, -2 } },{ 0b00010010,0b1,{ -1, -1 } } } },

			{ { { 0b10100001,0b0,{ -1, -3 } },{ 0b00011010,0b1,{ -1, -2 } },{ 0b00000100,0b0,{ -1, -1 } },{ 0b11000000,0b0,{ 0, -1 } } } },
			{ { { 0b10000001,0b0,{ 1, -3 } },{ 0b00010000,0b0,{ 0, -3 } },{ 0b00101100,0b1,{ 0, -2 } },{ 0b11000010,0b0,{ 0, -1 } } } },

			{ { { 0b00100100,0b1,{ 0, -2 } },{ 0b01000010,0b1,{ 0, -1 } } } },
			{ { { 0b10000100,0b1,{ 1, -1 } },{ 0b01001000,0b1,{ 0, -1 } } } },
		}
	};
	
	bool Path::Init(MapPoint Point) {
		bool f = false;
		Field *Game = Field::getInstance();
		
		Vec2 layerPosition = Game->mapLayer->getPosition();
		origin = { (int)round(layerPosition.x / (Game->scale * 10)), (int)round(layerPosition.y / (Game->scale * 10)) };

		Cell *startCell = &Game->cells[Point.x][Point.y];

		Area.e = { -1, -1 };
		Area.p = -1;
		int p = -1;
		bool pf = false;
		int Enter1 = -1;
		int Enter2 = -1;
		if (startCell->configuration != None) {
			for (int i = 0; i < 8; i++) {
				if (Enter1 == -1) {
					if (startCell->straightConnection[i] > 0) {
						Enter1 = i;
						Enter2 = Cell::Related[i];
						pf = true;
					}
				}
			}
		}

		if (pf) {
			Area.s = Point;
			Area.sc = startCell;
			graph(Point)->p = Point;
			for (int i = 0; i < 8; i++){
				graph(Point)->f[i] = false;
				graph(Point)->d[i] = 0;
				graph(Point)->e[i] = TrackElement::None;
				graph(Point)->In[i] = 0;
				graph(Point)->Out[i] = -1;
			}
			graph(Point)->d[Enter1] = 2;
			graph(Point)->d[Enter2] = 1;
			graph(Point)->isArea = true;
			GraphItems.insert(GraphItems.end(), graph(Point));			
			f = true;

			// debug
			/*debugNode = DrawNode::create();
			debugNode->setName("_debugItem");
			Game->mapLayer->addChild(debugNode, ZIndexRails);*/
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

		if ((Area.e.x == -1 && !(Area.s.x == Point.x && Area.s.y == Point.y)) || (Area.e.x >= 0 && !(Area.e.x == Point.x && Area.e.y == Point.y))) {
			changed = true;
		}
		MapPoint d;
		if (changed || Area.p != Enter) {			
			Area.p = Enter;
			Field *Game = Field::getInstance();
			Cell *current = &Game->cells[Point.x][Point.y];
			if (graph(Point)->isArea) {				
				int p = -1;
				if (graph(Point)->Out[Enter] >= 0 && graph(Point)->f[Enter] && graph(Point)->d[Enter] > 0) {
					p = Enter;
				}				
				if (p >= 0 && (Area.d.x != 0 || Area.d.y != 0)) {
					int i = 0;
					int nextPoint;
					Cell *next;
					PathItem *item;
					MapPoint c = { current->x, current->y }, n;
					bool a = true;
					vector<PathItem*> pathItems;
					while (a && graph(c)->d[p] > 0 && graph(c)->In[p] != 0) {

						TrackElement element = graph(c)->e[p];

						int enter = Elements::second[Path::track[element].entry[p]];
						
						next = graph(c)->In[p];
						n = { next->x, next->y };
						nextPoint = Cell::Related[graph(c)->Out[p]];
						
						for (auto l = 0; l < pathItems.size(); l++) {
							PathItem* item = pathItems[l];
							if (a) {
								a = checkIntersection({ item->next->x, item->next->y }, item->enter, item->elementType, n, enter, element);
							}
						}

						item = new PathItem;
						item->elementType = element;
						item->element = enter == 0 ? Elements::GetTrackElement(c, element) : Elements::GetTrackElement(n, element);
						item->enter = enter;
						item->next = next;
						item->current = current;
						item->point = p;
						pathItems.insert(pathItems.end(), item);

						p = nextPoint;
						current = next;
						c = { current->x, current->y };
						i++;
					}
					if (a) {
						for (auto c = 0; c < PathItems.size(); c++) {
							Game->mapLayer->removeChild(PathItems[c]->element, true);
						}
						PathItems.clear();
						for (auto c = 0; c < pathItems.size(); c++) {
							PathItems.insert(PathItems.end(), pathItems[c]);
							Game->mapLayer->addChild(pathItems[c]->element, ZIndexRails);
						}
					}
				} else if (Area.d.x == 0 && Area.d.y == 0) {
					for (auto c = 0; c < PathItems.size(); c++) {
						Game->mapLayer->removeChild(PathItems[c]->element, true);
					}
					PathItems.clear();									
				}
			}
		} //changed
				
		if (changed) {			
			Area.d.x = Point.x - Area.s.x;
			Area.d.y = Point.y - Area.s.y;
			Area.e = Point;
			Area.dt = abs(sqrt(pow(Area.d.x, 2) + pow(Area.d.y, 2)));
			Area.sin = (float)Area.d.y / (float)Area.dt;
			Area.cos = (float)Area.d.x / (float)Area.dt;
			
			for (auto i = BorderItems.begin(); i != BorderItems.end();) {
				if (Path::isArea(*i)) {
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

			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=] {
				Find(Area.sc);
			});
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

			pathCommand += StringUtils::format(("%s{\"cell\":{\"x\":%d,\"y\":%d},\"element\":\"" + Elements::getTrackElement(PathItems[c]->elementType) + "\",\"point\":%d}").c_str(),
				pathCommand == "" ? "" : ",", PathItems[c]->current->x, PathItems[c]->current->y, fromPoint);

			if (PathItems[c]->current->straightConnection[fromPoint] != NULL && PathItems[c]->current->divergingConnection[fromPoint] == NULL) {
				switchCommand += StringUtils::format("%s{\"cell\":{\"x\":%d,\"y\":%d},\"point\":%d}",
					switchCommand == "" ? "" : ",", PathItems[c]->current->x, PathItems[c]->current->y, fromPoint);
			}

			if (PathItems[c]->next->straightConnection[toPoint] != NULL && PathItems[c]->next->divergingConnection[toPoint] == NULL) {
				switchCommand += StringUtils::format("%s{\"cell\":{\"x\":%d,\"y\":%d},\"point\":%d}",
					switchCommand == "" ? "" : ",", PathItems[c]->next->x, PathItems[c]->next->y, toPoint);
			}
		}		
		PathItems.clear();
		
		string command = "path --add" + (pathCommand != "" ? " --path=[" + pathCommand + "]" : "") + (switchCommand != "" ? " --switch=[" + switchCommand + "]" : "");
		Cmd::Exec(command);

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
				Connect(c, p, TrackElement::SmallCilcleSect3, d + 314, 0);
				Connect(c, p, TrackElement::Crossover01, d + 322, 0);
				Connect(c, p, TrackElement::BaseCircleSect6, d + 321, 0);
				Connect(c, p, TrackElement::Horizontal, d + 100, 0);
				Connect(c, p, TrackElement::BaseCircleSect1, d + 321, 1);
				Connect(c, p, TrackElement::Crossover00, d + 322, 0);
				Connect(c, p, TrackElement::SmallCilcleSect0, d + 314, 1);
			}
			if (p == 1){
				Connect(c, p, TrackElement::BaseCircleSect7, d + 321, 0);
				Connect(c, p, TrackElement::Crossover11, d + 221, 0);
				Connect(c, p, TrackElement::Item45, d + 141, 0);
				Connect(c, p, TrackElement::Crossover10, d + 221, 0);
				Connect(c, p, TrackElement::BaseCircleSect2, d + 321, 1);
			}
			if (p == 2){
				Connect(c, p, TrackElement::SmallCilcleSect0, d + 314, 0);
				Connect(c, p, TrackElement::Crossover21, d + 322, 0);
				Connect(c, p, TrackElement::BaseCircleSect0, d + 321, 0);
				Connect(c, p, TrackElement::Vertical, d + 100, 1);
				Connect(c, p, TrackElement::BaseCircleSect3, d + 321, 1);
				Connect(c, p, TrackElement::Crossover20, d + 322, 0);
				Connect(c, p, TrackElement::SmallCilcleSect1, d + 314, 1);
			}
			if (p == 3){
				Connect(c, p, TrackElement::BaseCircleSect4, d + 321, 1);
				Connect(c, p, TrackElement::Crossover31, d + 221, 0);
				Connect(c, p, TrackElement::Item135, d + 141, 1);
				Connect(c, p, TrackElement::Crossover30, d + 221, 0);
				Connect(c, p, TrackElement::BaseCircleSect1, d + 321, 0);
			}
			if (p == 4){
				Connect(c, p, TrackElement::SmallCilcleSect2, d + 314, 1);
				Connect(c, p, TrackElement::Crossover00, d + 322, 1);
				Connect(c, p, TrackElement::BaseCircleSect5, d + 321, 1);
				Connect(c, p, TrackElement::Horizontal, d + 100, 1);
				Connect(c, p, TrackElement::BaseCircleSect2, d + 321, 0);
				Connect(c, p, TrackElement::Crossover01, d + 322, 1);
				Connect(c, p, TrackElement::SmallCilcleSect1, d + 314, 0);
			}
			if (p == 5){
				Connect(c, p, TrackElement::BaseCircleSect3, d + 321, 0);
				Connect(c, p, TrackElement::Crossover10, d + 221, 1);
				Connect(c, p, TrackElement::Item45, d + 141, 1);
				Connect(c, p, TrackElement::Crossover11, d + 221, 1);
				Connect(c, p, TrackElement::BaseCircleSect6, d + 321, 1);
			}
			if (p == 6){
				Connect(c, p, TrackElement::SmallCilcleSect3, d + 314, 1);
				Connect(c, p, TrackElement::Crossover20, d + 322, 1);
				Connect(c, p, TrackElement::BaseCircleSect7, d + 321, 1);
				Connect(c, p, TrackElement::Vertical, d + 100, 0);
				Connect(c, p, TrackElement::BaseCircleSect4, d + 321, 0);
				Connect(c, p, TrackElement::Crossover21, d + 322, 1);
				Connect(c, p, TrackElement::SmallCilcleSect2, d + 314, 0);
			}
			if (p == 7){
				Connect(c, p, TrackElement::BaseCircleSect0, d + 321, 1);
				Connect(c, p, TrackElement::Crossover30, d + 221, 1);
				Connect(c, p, TrackElement::Item135, d + 141, 0);
				Connect(c, p, TrackElement::Crossover31, d + 221, 1);
				Connect(c, p, TrackElement::BaseCircleSect5, d + 321, 0);
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

	void Path::Connect(Cell *out, int outPoint, TrackElement element, int d, int enter)
	{
		ElementOffset offset = Elements::offset[enter][element];
		MapPoint p = { out->x + offset.d.x, out->y + offset.d.y };		
		if (Path::inWindow(p)) {			
			if (Path::isArea(p)) {
				Cell *in = &Field::getInstance()->cells[p.x][p.y];
				int inPoint = offset.p;
				if (Path::isAllow(out, outPoint, enter, in, inPoint, Elements::second[enter] , element)) {
					GraphItem *i = graph({ in->x, in->y });
					if (i->d[inPoint] == 0 || (i->d[inPoint] > 0 && i->d[inPoint] > d)){
						i->d[inPoint] = d;
						i->e[inPoint] = element;
						i->In[inPoint] = out;
						i->Out[inPoint] = outPoint;
					}					
				}
			} else {
				if (!graph(p)->isBorder){
					BorderItems.insert(BorderItems.end(), p);
					graph(p)->isBorder = true;
				}				
			}
		}
	}

	bool Path::isArea(MapPoint Point){
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
					graph(Point)->e[i] = TrackElement::None;
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

	bool Path::isAllow(Cell *out, int outPoint, int outEnter, Cell *in, int inPoint, int inEnter, TrackElement element)
	{
		bool f = true;

		AccessItems accessItems = Path::access[outEnter][element];
		// check In
		if (in->configuration != Configuration::Undefined) {
			if (in->divergingConnection[inPoint] != 0) {
				f = false;
			}
			//not the same el
			if (f && in->straightConnection[inPoint] > 0 && in->straightConnection[inPoint]->Element == element) {				
				f = false;
			}
			//not right continue from end
			if (f && (in->straightConnection[inPoint] == 0 && in->straightConnection[Cell::Related[inPoint]] == 0)) {
				f = false;
			}			
			// check base circle
			if (f && in->configuration == Configuration::Polar) {
				f = checkBaseCircle(in, inPoint, inEnter, element);
			}
			//check crossover
			if (f) {
				f = checkCrossover(in, inPoint, inEnter, element);
			}
			//intersection 
			if (f && in->straightConnection[inPoint] > 0) {
				AccessItems accesInItems = Path::access[in->straightConnection[inPoint]->Enter][in->straightConnection[inPoint]->Element];
				accessItems = Path::getIntersection({ out->x, out->y }, accessItems, { in->x, in->y }, accesInItems);
			}
		}
		if (f) {
			f = checkBaseCircle(element, inEnter, graph({ in->x, in->y })->e[Cell::Related[inPoint]]);
		}
		if (f) {
			f = checkCrossover(element, inEnter, graph({ in->x, in->y })->e[Cell::Related[inPoint]]);
		}

		//check Out
		if (f && out->configuration != Configuration::Undefined) {
			if (out->divergingConnection[outPoint] != 0) {
				f = false;
			}
			if (f && out->straightConnection[outPoint] > 0 && out->straightConnection[outPoint]->Element == element) {
				f = false;
			}
			if (f && (out->straightConnection[outPoint] == 0 && out->straightConnection[Cell::Related[outPoint]] == 0)) {
				f = false;
			}
			if (f  && out->configuration == Configuration::Polar) {
				f = checkBaseCircle(out, outPoint, outEnter, element);			
			}
			if (f) {
				f = checkCrossover(out, outPoint, outEnter, element);
			}
			if (f && out->straightConnection[outPoint] > 0) {
				AccessItems accesOutItems = Path::access[out->straightConnection[outPoint]->Enter][out->straightConnection[outPoint]->Element];
				accessItems = Path::getIntersection({ out->x, out->y }, accessItems, { out->x, out->y }, accesOutItems);
			}
		}
		if (f) {
			f = checkBaseCircle(element, outEnter, graph({ out->x, out->y })->e[Cell::Related[outPoint]]);
		}
		if (f) {
			f = checkCrossover(element, outEnter, graph({ out->x, out->y })->e[Cell::Related[outPoint]]);
		}
		
		if (f) {			
			for (int i = 0; i < accessItems.items.size(); i++) {
				Cell cell = Field::getInstance()->cells[out->x + accessItems.items[i].p.x][out->y + accessItems.items[i].p.y];
				if (f && (cell.access > 0 || accessItems.items[i].c >0)) {
					if ((accessItems.items[i].access & cell.access) > 0 || (accessItems.items[i].c & cell.accessParam) > 0) {
						f = false;
					}
				}
			}
		}
		return f;
	}
	
	bool Path::checkIntersection(MapPoint point1, int enter1, TrackElement element1, MapPoint point2, int enter2, TrackElement element2)
	{
		bool f = true;
		AccessItems accessItems1 = Path::access[enter1][element1];
		AccessItems accessItems2 = Path::access[enter2][element2];
		if (f) {
			for (int i = 0; i < accessItems1.items.size(); i++) {
				for (int c = 0; c < accessItems2.items.size(); c++) {
					if (f && point1.x + accessItems1.items[i].p.x == point2.x + accessItems2.items[c].p.x && point1.y + accessItems1.items[i].p.y == point2.y + accessItems2.items[c].p.y && ((accessItems1.items[i].access & accessItems2.items[c].access) > 0 || (accessItems1.items[i].c & accessItems2.items[c].c) > 0)) {
						f = false;
					}
				}
			}
		}
		return f;
	}

	AccessItems Path::getIntersection(MapPoint point, AccessItems items, MapPoint intersectPoint, AccessItems intersectItems)
	{
		Field *game = Field::getInstance();
		for (int i = 0; i < intersectItems.items.size(); i++) {
			Cell intersectCell  = game->cells[intersectPoint.x + intersectItems.items[i].p.x][intersectPoint.y + intersectItems.items[i].p.y];
			for (int l = 0; l < items.items.size(); l++) {
				Cell cell = game->cells[point.x + items.items[l].p.x][point.y + items.items[l].p.y];
				if (cell.x == intersectCell.x && cell.y == intersectCell.y) {
					byte a = items.items[l].access;
					byte c = items.items[l].c;
					items.items[l].access = a ^ (a & intersectItems.items[i].access);
					items.items[l].c = c ^ (c & intersectItems.items[i].c);
				}
			}
		}
		return items;
	}
		
	bool Path::checkBaseCircle(Cell *cell, int point, int enter, TrackElement element)
	{
		bool f = true;
		int r = Cell::Related[point];
		TrackElement el1 = TrackElement::None, el2 = TrackElement::None;
		if (cell->straightConnection[r] > 0) {
			el1 = cell->straightConnection[r]->Element;
		}
		if (cell->divergingConnection[r] > 0) {
			el2 = cell->divergingConnection[r]->Element;
		}
		if (element == TrackElement::BaseCircleSect0 && enter == 1 && (el1 == TrackElement::BaseCircleSect1 || el2 == TrackElement::BaseCircleSect1)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect1 && enter == 0 && (el1 == TrackElement::BaseCircleSect0 || el2 == TrackElement::BaseCircleSect0)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect2 && enter == 1 && (el1 == TrackElement::BaseCircleSect3 || el2 == TrackElement::BaseCircleSect3)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect3 && enter == 0 && (el1 == TrackElement::BaseCircleSect2 || el2 == TrackElement::BaseCircleSect2)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect4 && enter == 1 && (el1 == TrackElement::BaseCircleSect5 || el2 == TrackElement::BaseCircleSect5)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect5 && enter == 0 && (el1 == TrackElement::BaseCircleSect4 || el2 == TrackElement::BaseCircleSect4)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect6 && enter == 1 && (el1 == TrackElement::BaseCircleSect7 || el2 == TrackElement::BaseCircleSect7)) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect7 && enter == 0 && (el1 == TrackElement::BaseCircleSect6 || el2 == TrackElement::BaseCircleSect6)) {
			f = false;
		}
		return f;
	}

	bool Path::checkBaseCircle(TrackElement element, int enter, TrackElement graphElement)
	{
		bool f = true;
		if (element == TrackElement::BaseCircleSect0 && enter == 1 && graphElement == TrackElement::BaseCircleSect1) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect1 && enter == 0 && graphElement == TrackElement::BaseCircleSect0) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect2 && enter == 1 && graphElement == TrackElement::BaseCircleSect3) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect3 && enter == 0 && graphElement == TrackElement::BaseCircleSect2) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect4 && enter == 1 && graphElement == TrackElement::BaseCircleSect5) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect5 && enter == 0 && graphElement == TrackElement::BaseCircleSect4) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect6 && enter == 1 && graphElement == TrackElement::BaseCircleSect7) {
			f = false;
		} else if (element == TrackElement::BaseCircleSect7 && enter == 0 && graphElement == TrackElement::BaseCircleSect6) {
			f = false;
		}
		return f;
	}
	
	bool Path::checkCrossover(Cell *cell, int point, int enter, TrackElement element)
	{
		bool f = true;
		int r = Cell::Related[point];
		TrackElement el1 = TrackElement::None, el2 = TrackElement::None;
		if (cell->straightConnection[r] > 0) {
			el1 = cell->straightConnection[r]->Element;
		}
		if (cell->divergingConnection[r] > 0) {
			el2 = cell->divergingConnection[r]->Element;
		}
				
		if ((element >= TrackElement::Crossover00 && element <= TrackElement::Crossover31) && ((el1 >= TrackElement::Crossover00 && el1 <= TrackElement::Crossover31) || (el2 >= TrackElement::Crossover00 && el2 <= TrackElement::Crossover31)) ) {
			f = false;
		}		
		return f;
	}

	bool Path::checkCrossover(TrackElement element, int enter, TrackElement graphElement)
	{
		bool f = true;
		if ((element >= TrackElement::Crossover00 && element <= TrackElement::Crossover31) && (graphElement >= TrackElement::Crossover00 && graphElement <= TrackElement::Crossover31)) {
			f = false;
		}		
		return f;
	}

	Vec2 Path::GetPosition(TrackPosition position)
	{
		Vec2 p = {0, 0};
		int s = Field::getInstance()->scale;
		MapPoint c = { position.cell->x, position.cell->y };
		if (position.indent > 0) {
			int indent;
			TrackItem _track = track[position.element];
			if (_track.entry[position.point] == 0) {
				indent = position.indent;
			} else {
				c.x -= _track.shift[0].x;
				c.y -= _track.shift[0].y;
				indent = _track.length - position.indent;
			}
			p = _track.items[indent] * s;
		}
		return { c.x * 10 * s + p.x,  c.y * 10 * s + p.y };
	}

	TrackPosition Path::GetPosition(TrackPosition position, int increase)
	{
		TrackPosition pos = position;
		int i = increase > 0 ? increase : -increase;
		Entry *entry;
		if (increase < 0) {			
			pos = backPosition(pos);
		}

		while (i > 0) {			
			entry = pos.cell->getEntry(pos.point, pos.element);			
			int TrackLength = track[entry->Element].length;
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
					pos.element = entry->to->getEntry(nextPoint)->Element;
				} else {
					pos.indent = TrackLength - i;
					i = 0;
				}
			}
		}

		if (increase < 0) {
			pos = backPosition(pos);
		}	
		return pos;
	}

	TrackPosition Path::backPosition(TrackPosition position)
	{
		Entry *entry = position.cell->getEntry(position.point, position.element);
		position.cell = entry->to;
		position.point = entry->Point;
		position.indent = track[entry->Element].length - position.indent - 1;
		return position;
	}
}
