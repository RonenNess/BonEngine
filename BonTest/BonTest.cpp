// EzTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "demos.h"
#include <iostream>


int main()
{
	std::cout << "Welcome to BonEngine demos!\nEnter demo number to run:\n";
	std::cout << " 1: Hello World\n";
	std::cout << " 2: Draw to Texture\n";
	std::cout << " 3: Basic input & Sound\n";
	std::cout << " 4: Spritesheet\n";
	std::cout << " 5: Lights\n";
	std::cout << " 6: Image filtering modes\n";
	std::cout << " 7: Imitate lower resolution in fullscreen\n";
	std::cout << " 8: Sound pitch effects\n";
	std::cout << " 9: Blend modes\n";
	std::cout << " 10: Drawing shapes\n";
	std::cout << " 11: Custom managers / collision\n";
	std::cout << " 12: Layered scenes\n";
	std::cout << " 13: A walk in the forest\n";
	std::cout << " 14: Switching scenes demo\n";
	std::cout << " 15: Performance test\n";
	std::cout << " 16: UI demo\n";
	std::cout << " 17: Effects demo (light scene)\n";
	std::cout << " 18: Rotation & Origin\n";
	std::cout << " 19: Texts\n";
	std::cout << "Your choice: ";

	int demoNumber = -1;
	bool gotValidInput = false;
	while (!gotValidInput) {

		std::cin >> demoNumber;
		std::cin.clear();
		std::cin.ignore();
		gotValidInput = true;
		switch (demoNumber)
		{
		case 1:
			demo1_hello_world::main();
			break;

		case 2:
			demo2_draw_to_texture::main();
			break;

		case 3:
			demo3_input_and_sound::main();
			break;

		case 4:
			demo4_spritesheet::main();
			break;

		case 5:
			demo5_lights::main();
			break;

		case 6:
			demo6_filtering_modes::main();
			break;

		case 7:
			demo7_fake_resolution::main();
			break;

		case 8:
			demo8_pitches::main();
			break;

		case 9:
			demo9_blend_modes::main();
			break;

		case 10:
			demo10_shapes::main();
			break;

		case 11:
			demo11_custom_manager::main();
			break;

		case 12:
			demo12_layered_scenes::main();
			break;

		case 13:
			demo13_a_walk_in_the_forest::main();
			break;

		case 14:
			demo14_switch_scenes::main();
			break;

		case 15:
			demo15_performance::main();
			break;

		case 16:
			demo16_ui::main();
			break;

		case 17:
			demo17_effects::main();
			break;

		case 18:
			demo18_rotation::main();
			break;

		case 19:
			demo19_texts::main();
			break;

		default:
			gotValidInput = false;
			break;
		}

		if (!gotValidInput) {
			std::cout << "Got invalid input.\nPlease insert a valid demo number to run: ";
		}
	}

	return 0;
}