

void antipodalPairs(std::list<Point2D> & puntos, std::list<std::pair<Point2D,Point2D> > & paresAntipodales){
    std::list<Point2D>::iterator p = puntos.end();
    p--;
    std::list<Point2D>::iterator q = puntos.begin();
    while(true){
        r = p++;
        if(r == puntos.end()) r++;
        if(areaTriangulo(p, r, q) > 
    }

}
