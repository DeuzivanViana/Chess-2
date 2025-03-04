#include <iostream>
#include <cmath>
#include <vector>
#include <raylib.h>

#define BOARD_SLOT_SIZE 52.f
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 720

Texture2D pieces_texture;

class Piece
{
public:
	Piece(const Texture2D &texture, const int piece_id) noexcept
		: __texture {&texture}, __piece_id {piece_id}
	{
		this->setPosition({0.f, 0.f});
	}

	virtual void setPosition(Vector2 position) noexcept
	{
		this->__position = position;
	}

	const Vector2 &getPosition() const noexcept
	{
		return this->__position;
	}

	virtual void draw(Camera2D camera) const noexcept
	{
		Vector2 frame_size = {
			this->__texture->width / 6.f,
			this->__texture->height / 2.f
		};

		Rectangle
			source =
			{
				frame_size.x * (this->__piece_id % 6), frame_size.y * (this->__piece_id / 6) ,
				frame_size.x, frame_size.y
			},
			dest = {
				this->__position.x, this->__position.y,
				BOARD_SLOT_SIZE, BOARD_SLOT_SIZE
			};


		DrawTexturePro(*this->__texture, source, dest, {0.f, 0.f}, 0.f, WHITE);
	}

	virtual ~Piece() noexcept
	{
	}

private:
	const Texture2D *__texture;
	Vector2 __position;
	int __piece_id;

};

class Board
{
public:
	Board() noexcept
		: __slot_size {BOARD_SLOT_SIZE}
	{
	}

	virtual void setPieceAt(int x, int y) noexcept
	{
	}

	virtual void draw(Camera2D camera) const noexcept
	{
		Vector2 mouse_position = GetMousePosition();
		Vector2 mouse_position_scorlled = GetScreenToWorld2D(mouse_position, camera);
		
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

		// Im testing something this is a bad comment and idc, cuz im programmer right now

		int x_index = std::floor(mouse_position_scorlled.x / BOARD_SLOT_SIZE);
		int y_index = std::floor(mouse_position_scorlled.y / BOARD_SLOT_SIZE);

		for(int i = 0; i < 8; i++)
		{
			int x = x_index + i;
			int y = y_index + i;
			
			DrawRectangleV({
				x * BOARD_SLOT_SIZE,
				y * BOARD_SLOT_SIZE
			}, {BOARD_SLOT_SIZE, BOARD_SLOT_SIZE}, GREEN);
			
			x = x_index - i;
			y = y_index + i;

			DrawRectangleV({
				x * BOARD_SLOT_SIZE,
				y * BOARD_SLOT_SIZE
			}, {BOARD_SLOT_SIZE, BOARD_SLOT_SIZE}, GREEN);


		}
		for(int i = 8; i > 0; i--)
		{
			int x = x_index - i;
			int y = y_index - i;
			
			DrawRectangleV({
				x * BOARD_SLOT_SIZE,
				y * BOARD_SLOT_SIZE
			}, {BOARD_SLOT_SIZE, BOARD_SLOT_SIZE}, GREEN);

			x = x_index + i;
			y = y_index - i;

			DrawRectangleV({
				x * BOARD_SLOT_SIZE,
				y * BOARD_SLOT_SIZE
			}, {BOARD_SLOT_SIZE, BOARD_SLOT_SIZE}, GREEN);

		}

	}
	
	virtual ~Board() noexcept
	{
	}
	
private:
	float __slot_size;
	std::vector<std::vector<Piece>> __slots;
};

int main(int, char*[])
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chess 2");

	Board table;
	Camera2D camera = {0};

	camera.offset = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f};
	camera.target = {BOARD_SLOT_SIZE * 8.f / 2.f, BOARD_SLOT_SIZE * 8.f / 2.f};
	camera.zoom = 1.f;

	pieces_texture = LoadTexture("assets/pieces.png");

	Piece pawn(pieces_texture, 5);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode2D(camera);

		table.draw(camera);
		pawn.draw(camera);

		EndMode2D();

		EndDrawing();
	}

	UnloadTexture(pieces_texture);

	CloseWindow();

	return EXIT_SUCCESS;
}
