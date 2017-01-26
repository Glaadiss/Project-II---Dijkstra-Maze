//
// Created by Bartłomiej Gładys on 17.01.2017.
//

#ifndef SFMLDEMO_VIEW_H
#define SFMLDEMO_VIEW_H

void render_app( point *head, std::vector<int> &values, std::vector<sf::CircleShape> &circles, sf::Vertex lines_array[][2], int r, bool *Q, sf::RenderWindow &app, int &point_id){
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        app.clear();
        for(int i = 0 ; i < 2 * numberOfPoints; ++i){
            app.draw(lines_array[i], 2, sf::Lines);
        }
        for(auto circle : circles){
            app.draw(circle);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            for(int i=0; i < circles.size(); ++i){
                if(circles[i].getPosition().x <= event.mouseButton.x && circles[i].getPosition().x + (r * 2) >= event.mouseButton.x){
                    if(circles[i].getPosition().y <= event.mouseButton.y && circles[i].getPosition().y + (r * 2) >= event.mouseButton.y){
                        point_id = i;
                    }
                }
            }
        }
        const int uninitializedId = -1;
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            for(int i=0; i < circles.size(); ++i){
                bool onXLeft = circles[i].getPosition().x <= event.mouseButton.x;
                bool onXRight = circles[i].getPosition().x + (r * 2) >= event.mouseButton.x;
                bool onYBootom = circles[i].getPosition().y <= event.mouseButton.y;
                bool onYHeight = circles[i].getPosition().y + (r * 2) >= event.mouseButton.y;
                if(onXLeft && onXRight && onYBootom && onYHeight){
                    for( int j = 0; j < numberOfPoints; j++ ){
                        from_head(j , head)->weight = 999; // big value, but can't be the biggest
                        from_head(j , head)->related_id = uninitializedId;
                        Q[j] = true;
                    }
                    dijkstra_alg(head, values, circles, lines_array, r, Q, i);
                }
            }
        }
        for(int i =0; i < circles.size(); ++i){
            circles[i].setFillColor(sf::Color::White);
        }
        while( point_id > -1){
            circles[point_id].setFillColor(sf::Color::Red);
            point_id = from_head(point_id , head)->related_id;
        }

        point *buffor = head->next;
        for(int i =0; i<numberOfPoints; i++){
            if(buffor->weight == 0)
                circles[buffor->id].setFillColor(sf::Color::Red);
            buffor = buffor->next;
        }
        app.display();
    }
}


#endif //SFMLDEMO_VIEW_H
