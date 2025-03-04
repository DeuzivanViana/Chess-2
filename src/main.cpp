#include <iostream>
#include <raylib.h>

#define TABLE_SLOT_SIZE 48.f

class Table
{
public:
	Table() noexcept
		: __slot_size {TABLE_SLOT_SIZE}
	{
	}

	virtual void draw(Camera2D camera) const noexcept
	{
		for(int y = 0; y < 8; y++)
		{
			for(int x = 0; x < 8; x++)
			{
				DrawRectangle(
					x * __slot_size,
					y * __slot_size,
					__slot_size,
					__slot_size,
					(x + y % 2) % 2 == 1 ? Color {118, 150, 86, 255} : Color {238, 238, 210, 255}
				);
			}
		}
	}

	virtual ~Table() noexcept
	{
	}
	
private:
	float __slot_size;
};

int main(int, char*[])
{
	InitWindow(480, 720, "Chess 2");

	Table table;
	Camera2D camera = {0};

	camera.offset = {0.f, 0.f};
	camera.target = {TABLE_SLOT_SIZE * 8.f, 0.f};
	camera.zoom = 1.f;

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		table.draw(camera);

		EndDrawing();
	}

	return EXIT_SUCCESS;
}
