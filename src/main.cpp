#include <iostream>
#include <raylib.h>

class Table
{
public:
	Table() noexcept
		: __slot_size {48.f}
	{
	}

	virtual void draw() const noexcept
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

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		table.draw();

		EndDrawing();
	}

	return EXIT_SUCCESS;
}
