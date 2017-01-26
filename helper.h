//
// Created by Bartłomiej Gładys on 17.01.2017.
//

#ifndef SFMLDEMO_HELPER_H
#define SFMLDEMO_HELPER_H



void set_params(point *head,  std::vector<int> &, std::vector<sf::CircleShape> &, sf::Vertex lines_array[][2], int r , bool *, int start_point, int big_val);
void dijkstra_alg(point *head,  std::vector<int> &, std::vector<sf::CircleShape> &, sf::Vertex lines_array[][2], int r , bool *, int start_point);
void render_app(point *head, std::vector<int> &, std::vector<sf::CircleShape> &, sf::Vertex lines_array[][2], int , bool *, sf::RenderWindow&, int &);

void fill_points_and_circles(point *head, std::vector<sf::CircleShape> &circles, int r, bool *Q, int big_val){
    point *buffor = head;
    for(int i =0; i<pointsInRow; ++i){
        for(int g =0; g<pointsInRow; ++g){
            sf::CircleShape circle;
            circle.setRadius(r);
            circle.setPosition(r * g * convertedWidth + convertedHeight, r * i * convertedWidth + convertedHeight);
            circle.setOutlineColor(sf::Color::Red);
            circle.setFillColor(sf::Color::White);
            circles.push_back(circle);
            short int iter = i * pointsInRow + g;
            point *new_point = new point;
            new_point->id = iter;
            new_point->weight = big_val;
            new_point->related_id = -1;
            new_point->top = big_val;
            new_point->right = big_val;
            new_point->left = big_val;
            new_point->bot = big_val;
            buffor->next = new_point;
            buffor = new_point;
            Q[iter] = true;
        }
    }

}


void connecting_circles_horizontaly(point *head, std::vector<int> &values, std::vector<sf::CircleShape> &circles, sf::Vertex lines_array[][2], int r, int big_val){
    for( int i =1; i<numberOfPoints; ++i ){
        if ( i % pointsInRow != 0  && rand()%9 > 3 ){
            from_head(i - 1, head)->right = 1;
            from_head(i , head)->left = 1;
            lines_array[i][0] = sf::Vertex(sf::Vector2f( circles[i-1].getPosition().x + r , circles[i-1].getPosition().y + r ));
            lines_array[i][1] = sf::Vertex(sf::Vector2f( circles[i].getPosition().x + r, circles[i].getPosition().y + r));
        }
        else {
            from_head(i - 1, head)->right = big_val;
            from_head(i , head)->left = big_val;
            values[i] = big_val;
        }
    }
}

void connecting_circles_verticaly(point *head,  std::vector<int> &values, std::vector<sf::CircleShape> &circles, sf::Vertex lines_array[][2], int r, int big_val){
    for( int i =0; i< numberOfPoints / pointsInRow ; ++i ){
        if ( rand()%9 > 3 ){
            from_head(i , head)->bot = 1;
            from_head(i + pointsInRow, head)->top = 1;
            lines_array[i + numberOfPoints][0] = sf::Vertex(sf::Vector2f( circles[i].getPosition().x + r, circles[i].getPosition().y + r ), sf::Color::White);
            lines_array[i + numberOfPoints][1] = sf::Vertex(sf::Vector2f( circles[i + 10].getPosition().x + r, circles[i + 10].getPosition().y + r), sf::Color::White);
        }
        else{
            from_head(i , head)->bot = big_val;
            from_head(i + pointsInRow , head)->top = big_val;
            values [i +numberOfPoints] = big_val;
        }
    }

}

void dijkstra_alg(point *head, std::vector<int> &values, std::vector<sf::CircleShape> &circles, sf::Vertex lines_array[][2], int r, bool *Q, int start_point){
    from_head(start_point , head)->weight = 0;
    for(int i =0; i<numberOfPoints; i++) {
        point *interim = new point;
        interim->weight = std::numeric_limits<int>::max();
        point *secondBuffor = head->next;
        for(int k =0; k<numberOfPoints; k++){
            if(interim->weight > secondBuffor->weight && Q[secondBuffor->id])
                interim = secondBuffor;

            secondBuffor = secondBuffor->next;
        }

        Q[interim->id] = false;
        int cords[4] = {pointsInRow , -1 , -pointsInRow , 1};
        for(int j =0; j < convertedWidth; ++j){
            if( interim->id - cords[j] < numberOfPoints && interim->id - cords[j] >= 0 && Q[interim->id -cords[j]] ){
                if( from_head(interim->id - cords[j], head)->weight > interim->weight + interim->get_direction(j) ){
                    from_head(interim->id - cords[j], head)->weight = interim->weight + interim->get_direction(j) ;
                    from_head(interim->id - cords[j], head)->related_id = interim->id ;
                }
            }
        }
    }
}

void set_params(point *head, std::vector<int> &values, std::vector<sf::CircleShape> &circles, sf::Vertex lines_array[][2], int r, bool *Q, int start_point, int big_val){
    fill_points_and_circles(head, circles, r, Q, big_val);
    connecting_circles_horizontaly(head, values, circles, lines_array, r, big_val);
    connecting_circles_verticaly(head, values, circles, lines_array, r, big_val );
    dijkstra_alg(head, values, circles, lines_array, r, Q, start_point);
}

#endif //SFMLDEMO_HELPER_H
