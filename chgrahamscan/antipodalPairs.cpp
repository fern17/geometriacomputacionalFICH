

void antipodalPairs(std::list<Point2D> &Q, std::list<std::pair<Point2D, Point2D> > &pairs){
    std::list<Point2D>::iterator p = Q.end()-1,
                                 q = Q.begin(),
                                 nextp, nextq,
                                 q0, p0 = Q.begin();
    pairs.clear();

    nextp = p;
    nextp++;
    if( nextp == Q.end()) 
        nextp = Q.begin();
    
    nextq = q;
    nextq++;
    if( nextq == Q.end())
        nextq = Q.begin();

    while(areaTriangle(*p, *nextp, *nextq) > areaTriangle(*p, *nextp, q)){
        q = nextq;
        nextq++;
        if(q == Q.end())
            q = Q.begin();
    }
    
    q0 = q;

    while( p != p0){
        p = nextp;

        std::pair<Point2D,Point2D> pq = std::make_pair(*p,*q);
        pairs.push_back(pq);
        
        while( areaTriangle(*p, *nextp, *nextq) > areaTriangle(*p, *nextp, *q)){
            q = nextq;
            nextq++;
            if(q == Q.end())
                q = Q.begin();
            pq = std::make_pair(*p,*q);
            if(pq != std::make_pair(*q0, *p0))
                pairs.push_back(pq);
            else
                return;
        }
        
        if(compareEqualFloat( areaTriangle(*p, *nextp, *nextq), areaTriangle(*p, *nextp, *nextq))){
            if(pq != std::make_pair(*q0,Q.last()))
                pairs.push_back(std::make_pair(*p, *nextq));
            else
                pairs.push_back(std::make_pair(*nextp, *q));
        }

    }
}
