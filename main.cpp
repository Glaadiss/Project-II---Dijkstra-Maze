#include "point.h"
#include "helper.h"
#include "view.h"

int main(){
    srand(time(0));
    const int r = 30;
    sf::RenderWindow app(sf::VideoMode(1600, 1600), "SFML window");
    sf::Vertex lines_array[2 * numberOfPoints ][2]; // number of lines in haze SFML
    std::vector<int> values(190, 1);  // number of lines in haze
    std::vector<sf::CircleShape> circles;
    bool Q[numberOfPoints];
    int point_id = 0;
    int start_point = 0;
    const int big_val = 999; // big val, but can't be the biggest!
    point *head = new point;
    set_params(head, values, circles, lines_array, r, Q, start_point, big_val);
    render_app(head, values, circles, lines_array, r, Q, app, point_id);
    return EXIT_SUCCESS;
}




// to other file ( frontend )
