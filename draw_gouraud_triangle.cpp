#include <QImage>
#include <QColor>

#include <math.h>

void Draw_Gouraud_Triangle(QImage &image, /* int w, int h, int pitch, */
            int x0, int y0, float r0, float g0, float b0, float a0,
                  int x1, int y1, float r1, float g1, float b1, float a1,
                  int x2, int y2, float r2, float g2, float b2, float a2)

{

float tmp;
#define SWAP(a,b) { tmp = a; a = b; b = tmp; }
#define CLAMP(x) (isfinite((x)) ? (((x) < 0) ? (0) : (((x) > 255) ? 255 : (x))) : 0)
#define CLAMP2(x,d) (((x) < 0) ? (0) : (((x) >= (d)) ? ((d) - 1) : (x)))

      // Sort our points into order of y
      // 0 top
      // 2 middle
      // 1 bottom

      int w = image.width();
      int h = image.height();

      if( y1 < y0 ) {
	    SWAP(y1, y0);
	    SWAP(x1, x0);
        SWAP(r1, r0);  SWAP(g1, g0);  SWAP(b1, b0); SWAP(a1, a0);
      }

      if( y2 < y0 ) {
	    SWAP(y2, y0);
	    SWAP(x2, x0);
        SWAP(r2, r0);  SWAP(g2, g0);  SWAP(b2, b0); SWAP(a2, a0);
      }

      if( y1 < y2 ) {
	    SWAP(y2, y1);
	    SWAP(x2, x1);
        SWAP(r2, r1);  SWAP(g2, g1);  SWAP(b2, b1); SWAP(a2, a1);
      }

      float xl_edge = (float)x0;  // left edge
      float xr_edge = (float)x0;  // right edge

      float dxldy;
      float dxrdy;

      float dxdy1 = (float)(x2-x0)/(y2-y0);
      float dxdy2 = (float)(x1-x0)/(y1-y0);

      float dr1 = (float)(r2-r0)/(y2-y0);
      float dg1 = (float)(g2-g0)/(y2-y0);
      float db1 = (float)(b2-b0)/(y2-y0);
      float da1 = (float)(a2-a0)/(y2-y0);

      float dr2 = (float)(r1-r0)/(y1-y0);
      float dg2 = (float)(g1-g0)/(y1-y0);
      float db2 = (float)(b1-b0)/(y1-y0);
      float da2 = (float)(a1-a0)/(y1-y0);

      float drldy, dgldy, dbldy, daldy;
      float drrdy, dgrdy, dbrdy, dardy;

      if( dxdy1 < dxdy2 ) {
	    dxldy = dxdy1;
	    dxrdy = dxdy2;

        drldy  = dr1;     dgldy  = dg1;     dbldy  = db1; daldy = da1; // left  (r,g,b)
        drrdy  = dr2;     dgrdy  = dg2;     dbrdy  = db2; dardy = da2; // right (r,g,b)
      } else {
	    dxldy = dxdy2;
	    dxrdy = dxdy1;
        drldy  = dr2;     dgldy  = dg2;     dbldy  = db2; daldy = da2; // left  (r,g,b)
        drrdy  = dr1;     dgrdy  = dg1;     dbrdy  = db1; dardy = da1; // right (r,g,b)
      }

      float r_left  = r0;
      float r_right = r0;
      float g_left  = g0;
      float a_left  = a0;
      float g_right = g0;
      float b_left  = b0;
      float b_right = b0;
      float a_right = a0;


      // Top of the triangle
      for(int y=y0; y<y2; y++) {
	    float dr = (r_right - r_left)/(xr_edge - xl_edge);
	    float dg = (g_right - g_left)/(xr_edge - xl_edge);
	    float db = (b_right - b_left)/(xr_edge - xl_edge);
        float da = (a_right - a_left)/(xr_edge - xl_edge);

	    float pr = r_left;
	    float pg = g_left;
	    float pb = b_left;
        float pa = a_left;

	    for(int x=xl_edge; x<xr_edge; x++) {
		  pr = pr + dr;
		  pg = pg + dg;
		  pb = pb + db;
          pa = pa + da;

		  if (x >= 0 && x < w && y >= 0 && y < h)
            image.setPixel(QPoint(x, y), QColor(CLAMP(pr), CLAMP(pg), CLAMP(pb), CLAMP(pa)).rgba());

	    }//end for loop x

	    xl_edge = xl_edge + dxldy;
	    xr_edge = xr_edge + dxrdy;


	    r_left  += drldy;
	    r_right += drrdy;

	    g_left  += dgldy;
	    g_right += dgrdy;

	    b_left  += dbldy;
	    b_right += dbrdy;

        a_left  += daldy;
        a_right += dardy;
      }// end for loop y

      // Bottom half of the triangle
      if (y0 == y2) {
	      if (x0 > x2) {
		      xr_edge = x0;
		      r_right = r0;
		      g_right = g0;
		      b_right = b0;
              a_right = a0;

		      xl_edge = x2;
		      r_left = r2;
		      g_left = g2;
		      b_left = b2;
              a_left = a2;
	      } else {
		      xr_edge = x2;
		      r_right = r2;
		      g_right = g2;
		      b_right = b2;
              a_right = a2;

		      xl_edge = x0;
		      r_left = r0;
		      g_left = g0;
		      b_left = b0;
              a_left = a0;
	      }
      }

      if( dxdy1 < dxdy2 ) {
	    dxldy = (float)(x2-x1)/(y2-y1);

	    drldy  = (r2-r1)/(y2-y1);
	    dgldy  = (g2-g1)/(y2-y1);
	    dbldy  = (b2-b1)/(y2-y1);
        daldy  = (a2-a1)/(y2-y1);
      } else {
	    dxrdy = (float)(x2-x1)/(y2-y1);

	    drrdy  = (r2-r1)/(y2-y1);
	    dgrdy  = (g2-g1)/(y2-y1);
	    dbrdy  = (b2-b1)/(y2-y1);
        dardy  = (a2-a1)/(y2-y1);
      }

      for(int y=y2; y<y1; y++) {
	    float dr = (r_right - r_left)/(xr_edge - xl_edge);
	    float dg = (g_right - g_left)/(xr_edge - xl_edge);
	    float db = (b_right - b_left)/(xr_edge - xl_edge);
        float da = (a_right - a_left)/(xr_edge - xl_edge);

	    float pr = r_left;
	    float pg = g_left;
	    float pb = b_left;
        float pa = a_left;

	    for(int x=xl_edge; x<xr_edge; x++) {
		  pr = pr + dr;
		  pg = pg + dg;
		  pb = pb + db;
          pa = pa + da;

		  if (x >= 0 && x < w && y >= 0 && y < h)
            image.setPixel(QPoint(x, y), QColor(CLAMP(pr), CLAMP(pg), CLAMP(pb), CLAMP(pa)).rgba());

	    } //end for loop x

	    xl_edge = xl_edge + dxldy;
	    xr_edge = xr_edge + dxrdy;

	    r_left  += drldy;
	    r_right += drrdy;

	    g_left  += dgldy;
	    g_right += dgrdy;

	    b_left  += dbldy;
	    b_right += dbrdy;

        a_left  += daldy;
        a_right += dardy;
      }// end for loop y
}
