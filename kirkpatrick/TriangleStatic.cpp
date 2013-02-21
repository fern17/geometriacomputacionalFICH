
static TriangleStatic TriangleStatic::buildFromTriangle(Triangle T) {
    Point p1 = T.p1->p;
    Point p2 = T.p2->p;
    Point p3 = T.p3->p;
    TriangleStatic ret_val (p1, p2, p3);
    return ret_val;
}
