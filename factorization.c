#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// .c -> .txt //

//todo case4 wa to sa no seki //
int euclid( int a, int b )
{
	int temp;

	if( a < b ) { temp = a; a = b; b = temp; }
	if( b < 1 ) return -1;

	if( a % b == 0 ) return b;
	return euclid( b, a % b );
}

int main(int argc, char *argv[]){
	FILE *fp1,*fp2;
	fp1 = fopen("factorization.txt","w");
	fp2 = fopen("factorization_answer.txt","w");
	if( fp1 == NULL ){
		printf("Cannot open file\n");
		return 1;
	}
	if( fp2 == NULL ){
		printf("Cannot open file\n");
		return 1;
	}
	srand( ( unsigned int ) time ( NULL ) );
	int randnum, type, questions = 1, num_of_questions = atoi(argv[1]), a, b, c, d, e, f, g, h, qa, qb, qc, qd, qe, qf, qg, qh, aa, ab, ac, ad, ae, af, ag, ah;
	int gcd_bc,gcd_de;
	char pmqa[2],pmqb[2], pmqc[2], pmqd[2], pmqe[2], pmqf[2], pmqg[2], pmqh[2];
	char pma[2], pmb[2], pmc[2], pmd[2], pme[2], pmf[2], pmg[2], pmh[2];
	while( questions <= num_of_questions ){
		type = rand() % 9 + 1;
		switch( type ){
			case 1 :
				RESET1:
				b = rand() % 10 + 1;
				c = ( rand() % 20 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				d = rand() % 10 + 1;
				e = ( rand() % 20 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				gcd_bc = euclid( b, abs( c ) );
				b /= gcd_bc;
				c /= gcd_bc;
				gcd_de = euclid( d, abs( e ) );
				d /= gcd_de;
				e /= gcd_de;

				a = gcd_bc * gcd_de * ( 1 - 2 * ( rand() % 2 ) ) * ( rand() % 2 + 1 );

				qa = a * b * d;
				qb = a * ( b * e + c * d);
				if(qb > 0) pmqb[0] = '+';
				else if( qb == 0 ) goto RESET1;
				else pmqb[0] = '-';
				qc = a * c * e;
				if( qc > 0 ) pmqc[0] = '+';
				else if( qc == 0 ) break;
				else pmqc[0] = '-';

				if( c >= 0) pmc[0] = '+';
				else pmc[0] = '-';
				if( e >= 0) pme[0] = '+';
				else pme[0] = '-';

				if ( qa == 1 ) fprintf( fp1, "(%d) x^2 %c %dx %c %d \n", questions, pmqb[0], abs( qb ), pmqc[0], abs( qc ) );
				else if ( qa == -1 ) fprintf( fp1, "(%d) -x^2 %c %dx %c %d \n", questions, pmqb[0], abs( qb ), pmqc[0], abs( qc ) );
				else fprintf ( fp1, "(%d) %dx^2 %c %dx %c %d\n",questions, qa, pmqb[0], abs( qb ), pmqc[0], abs( qc ) );
				// fprintf( fp2, "(%d) %d(%dx %c %d)(%dx %c %d)\n", questions, a, b, pmc[0], abs( c ), d, pme[0], abs( e ) );
				if( abs( a ) !=1 )fprintf( fp2, "(%d) %d", questions , a );
				else if( a == -1 )fprintf( fp2, "(%d) -", questions );
				else fprintf( fp2, "(%d) ", questions );

				if( abs( b ) !=1 )fprintf( fp2, "(%dx ", b );
				else if( b == -1 )fprintf( fp2, "(-x ");
				else fprintf( fp2, "(x");

				fprintf( fp2, "%c %d)(", pmc[0], abs ( c ) );

				if( abs( d ) !=1 )fprintf( fp2, "%dx ", d );
				else if( d == -1 )fprintf( fp2, "-x ");
				else fprintf( fp2, "x ");

				fprintf( fp2, "%c %d)\n", pme[0], abs ( e ) );

				break;
				
			case 2 :
			//a(cx+b)(cx-b) = ac^2x^2 - a*b^2//
				a = ( rand() % 3 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				b = rand() % 9 + 2;
				c = rand() % 9 + 2;
				int case2_gcd_bc = euclid( b, c );
				a *= case2_gcd_bc ;
				b /= case2_gcd_bc ;
				c /= case2_gcd_bc ;
				if( a > 0 ) pmqa[0] = '-';
				else pmqa[0] = '+';

				if( a * c * c == 1 ) fprintf( fp1, "(%d) x^2 %c %d\n", questions, pmqa[0], abs( a * b * b ) );
				else if( a * c * c == -1 ) fprintf( fp1, "(%d) -x^2 %c %d\n", questions, pmqa[0], abs( a * b * b ) );				
				else fprintf( fp1, "(%d) %dx^2 %c %d\n", questions, a * c * c, pmqa[0], abs( a * b * b ) );
				if ( abs ( a ) != 1 && c != 1 )fprintf( fp2, "(%d) %d(%dx + %d)(%dx - %d)\n", questions, a, c, b, c, b );
				else if ( abs ( a ) != 1 && c == 1 )fprintf( fp2, "(%d) %d(x + %d)(x - %d)\n", questions, a, b, b );
				else if ( a == 1 && c != 1 )fprintf( fp2, "(%d) (%dx + %d)(%dx - %d)\n", questions, c, b, c, b );
				else if ( a == 1 && c == 1 )fprintf( fp2, "(%d) (x + %d)(x - %d)\n", questions, b, b );
				else if ( a == -1 && c !=1 )fprintf( fp2, "(%d) -(%dx + %d)(%dx - %d)\n", questions, c, b, c, b );
				else if ( a == -1 && c ==1 )fprintf( fp2, "(%d) -(x + %d)(x - %d)\n", questions, b, b );

				break;

			case 3 :
			// a(bx+cy+d)(ex+fy+g) = qax^2 + qbxy + qcy^2 + qdx + qey + qf//
			// A = bx+cy type//
				RESET3:
				b = ( rand() % 3 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				e = ( rand() % 3 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				c = ( rand() % 3 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				f = ( rand() % 3 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				d = ( rand() % 9 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				g = ( rand() % 9 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				if( d == g ) goto RESET3;
				int case5_gcd_bcd = euclid( euclid( abs( b ), abs( c ) ), abs ( d ) );
				int case5_gcd_efg = euclid( euclid( abs( e ), abs( f ) ), abs ( g ) );
				b /= case5_gcd_bcd;
				c /= case5_gcd_bcd;
				d /= case5_gcd_bcd;
				e /= case5_gcd_efg;
				f /= case5_gcd_efg;
				g /= case5_gcd_efg;

				a = case5_gcd_bcd * case5_gcd_efg * ( 1 - 2 * ( rand() % 2 ) );

				if( b < 0 ){
					a *= -1;
					b *= -1;
					c *= -1;
					d *= -1;
				}
				if ( e < 0 ){
					a *= -1;
					e *= -1;
					f *= -1;
					g *= -1;
				}

				qa = a * b * e;
				qb = a * ( b * f + c * e );
				qc = a * c * f;
				qd = a * ( b * g + d * e );
				qe = a * ( c * g + d * f );
				qf = a * d * g;
				int case5_flag = 0;
				if( qb > 0 ) pmqb[0] = '+';
				else if( qb < 0 ) pmqb[0] = '-';
				else goto RESET3;
				if( qc > 0 ) pmqc[0] = '+';
				else if( qc < 0 ) pmqc[0] = '-';
				else goto RESET3;
				if( qd > 0 ) pmqd[0] = '+';
				else if( qd < 0 ) pmqd[0] = '-';
				else goto RESET3;
				if( qe > 0 ) pmqe[0] = '+';
				else if( qe < 0 ) pmqe[0] = '-';
				else goto RESET3;
				if( qf > 0 ) pmqf[0] = '+';
				else if( qf < 0 ) pmqf[0] = '-';
				else goto RESET3;
				if( c >= 0) pmc[0] = '+';
				else pmc[0] = '-';
				if( d >= 0) pmd[0] = '+';
				else pmd[0] = '-';
				if( f >= 0) pmf[0] = '+';
				else pmf[0] = '-';
				if( g >= 0) pmg[0] = '+';
				else pmg[0] = '-';

				fprintf( fp1, "(%d) %dx^2 %c %dxy %c %dy^2 %c %dx %c %dy %c %d\n", questions, qa, pmqb[0], abs( qb ), pmqc[0], abs( qc ), pmqd[0], abs( qd ), pmqe[0], abs( qe ), pmqf[0], abs( qf ) );
				// fprintf( fp2, "(%d) %d(%dx %c %dy %c %d)(%dx %c %dy %c %d)\n", questions, a, b, pmc[0], abs( c ), pmd[0], abs( d ), e, pmf[0], abs( f ), pmg[0], abs( g ) );
				
				fprintf( fp2, "(%d) ", questions );
				if ( a  == 1 ) fprintf( fp2, "");
				else if ( a == -1 ) fprintf( fp2, "-");
				else fprintf( fp2, "%d", a );
				
				if ( b  == 1 ) fprintf( fp2, "(x ");
				else if ( b == -1 ) fprintf( fp2, "(-x ");
				else fprintf( fp2, "(%dx ", b );

				if ( abs( c ) != 1 ) fprintf( fp2, "%c %dy %c %d)", pmc[0], abs( c ), pmd[0], abs( d ) );
				else fprintf( fp2, "%c y %c %d)", pmc[0], pmd[0], abs( d ) );
				
				if ( e  == 1 ) fprintf( fp2, "(x ");
				else if ( e == -1 ) fprintf( fp2, "(-x ");
				else fprintf( fp2, "(%dx ", e );

				if ( abs( f ) != 1 ) fprintf( fp2, "%c %dy %c %d)\n", pmf[0], abs( f ) , pmg[0], abs( g ) );
				else fprintf( fp2, "%c y %c %d)\n", pmf[0], pmg[0], abs( g ) );

				break;

			case 4 :
				// a( bx + cy + dz)^2 = qax^2 + qby^2 +qcz^2 + qdxy + qeyz + qfzx //
				b = ( rand() % 5 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				c = ( rand() % 5 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				d = ( rand() % 5 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				a = euclid( euclid( abs( b ) , abs( c ) ), abs( d ) );
				b /= a;
				c /= a;
				d /= a;
				qa = a * b * b;
				qb = a * c * c;
				qc = a * d * d;
				qd = 2 * a * b * c;
				qe = 2 * a * c * d;
				qf = 2 * a * b * d;

				if( qb >= 0 ) pmqb[0] = '+';
				else pmqb[0] = '-';
				if( qc >= 0 ) pmqc[0] = '+';
				else pmqc[0] = '-';
				if( qd >= 0) pmqd[0] = '+';
				else pmqd[0] = '-';
				if( qe >= 0) pmqe[0] = '+';
				else pmqe[0] = '-';
				if( qf > 0 ) pmqf[0] = '+';
				else pmqf[0] = '-';

				if( c > 0 ) pmc[0] = '+';
				else pmc[0] = '-';
				if( d > 0 ) pmd[0] = '+';
				else pmd[0] = '-';

				if( b < 0 && c < 0 && d < 0){
					pmb[0] = '+';
					pmc[0] = '+';
					pmd[0] = '+';
				}

				fprintf( fp1, "(%d) %dx^2 %c %dy^2 %c %dz^2 %c %dxy %c %dyz %c %dzx\n", questions, qa, pmqb[0], abs( qb ), pmqc[0], abs( qc ), pmqd[0], abs( qd ), pmqe[0], abs( qe ), pmqf[0], abs( qf ) );
				// a(bx + cy + dz)^2
				if( abs( a ) != 1 )fprintf( fp2, "(%d) %d(", questions, a );
				else if( a == 1 )fprintf( fp2, "(%d) (", questions );
				else fprintf( fp2, "(%d) -(", questions );
				if( abs( b ) != 1 )fprintf( fp2, "%dx ", b );
				else if( b == 1 )fprintf( fp2, "x ");
				else fprintf( fp2, "-x ");
				if( abs( c ) != 1 )fprintf( fp2, "%c %dy ", pmc[0], abs( c ) );
				else fprintf( fp2, "%c y ", pmc[0] );
				if( abs( d ) != 1 )fprintf( fp2, "%c %dz)^2\n", pmd[0], abs( d ) );
				else fprintf( fp2, "%c z)^2\n", pmd[0] );
				break;

			case 5 :
			// a( bx + cy + d )^2 = qax^2 + qby^2 +qc2 + qfx + qdxy + qey //
				b = ( rand() % 5 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				c = ( rand() % 5 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				d = ( rand() % 5 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				a = euclid( euclid( abs( b ) , abs( c ) ), abs( d ) );
				b /= a;
				c /= a;
				d /= a;
				qa = a * b * b;
				qb = a * c * c;
				qc = a * d * d;
				qd = 2 * a * b * c;
				qe = 2 * a * c * d;
				qf = 2 * a * b * d;

				if( qb >= 0 ) pmqc[0] = '+';
				else pmqb[0] = '-';
				if( qc >= 0 ) pmqc[0] = '+';
				else pmqc[0] = '-';
				if( qd >= 0) pmqd[0] = '+';
				else pmqd[0] = '-';
				if( qe >= 0) pmqe[0] = '+';
				else pmqe[0] = '-';
				if( qf > 0 ) pmqf[0] = '+';
				else pmqf[0] = '-';

				if( c > 0 ) pmc[0] = '+';
				else pmc[0] = '-';
				if( d > 0 ) pmd[0] = '+';
				else pmd[0] = '-';

				if( b < 0 && c < 0 && d < 0){
					pmb[0] = '+';
					pmc[0] = '+';
					pmd[0] = '+';
				}

				// a( bx + cy + d )^2 = qax^2 + qby^2 + qfx + qdxy + qey + qc^2 //
				fprintf( fp1, "(%d) %dx^2 %c %dy^2 %c %dx %c %dxy %c %dy %c %d\n", questions, qa, pmqb[0], abs( qb ), pmqf[0], abs( qf ), pmqd[0], abs( qd ), pmqe[0], abs( qe ), pmqc[0], abs( qc ) );
				// a(bx + cy + d)^2
				if( abs( a ) != 1 )fprintf( fp2, "(%d) %d(", questions, a );
				else if( a == 1 )fprintf( fp2, "(%d) (", questions );
				else fprintf( fp2, "(%d) -(", questions );
				if( abs( b ) != 1 )fprintf( fp2, "%dx ", b );
				else if( b == 1 )fprintf( fp2, "x ");
				else fprintf( fp2, "-x ");
				if( abs( c ) != 1 )fprintf( fp2, "%c %dy ", pmc[0], abs( c ) );
				else fprintf( fp2, "%c y ", pmc[0] );
				fprintf( fp2, "%c %d)^2\n", pmd[0], abs( d ) );
				break;

			case 6:
				randnum = rand() % 21 + 1;
					switch( randnum ){
						case 1 :
						fprintf( fp1, "(%d) x^2 - (y - z)^2\n", questions );
						fprintf( fp2, "(%d) (x - y + z)(x + y - z)\n", questions );
						break;
						case 2 :
						fprintf( fp1, "(%d) ax + bx + a^2 - b^2\n", questions );
						fprintf( fp2, "(%d) (a + b)(x + a - b)\n", questions );
						break;
						case 3 :
						fprintf( fp1, "(%d) a^2 - 2b^2 - ab + bc + ac - a + 2b - c\n", questions );
						fprintf( fp2, "(%d) (a + b - 1)(c + a - 2b)\n", questions );
						break;
						case 4 :
						fprintf( fp1, "(%d) abx^2 - (a^2 + b^2)x + ab\n", questions );
						fprintf( fp2, "(%d) (ax - b)(bx - a)\n", questions );
						break;
						case 5 :
						fprintf( fp1, "(%d) 9a^2 b - 6ac\n", questions );
						fprintf( fp2, "(%d) 3a(3ab - 2c)\n", questions );
						break;
						case 6 :
						fprintf( fp1, "(%d) 3x^2 yz + yz\n", questions );
						fprintf( fp2, "(%d) yz(3x^2 + 1)\n", questions );
						break;
						case 7 :
						fprintf( fp1, "(%d) 4x^2 y + 6xy^3\n", questions );
						fprintf( fp2, "(%d) 2xy(2x + 3y^2)\n", questions );
						break;			
						case 8 :
						fprintf( fp1, "(%d) (x + y)^2 + 2(x + y) - 8\n", questions );
						fprintf( fp2, "(%d) (x + y + 4)(x + y - 2)\n", questions );
						break;	
						case 9 :
						fprintf( fp1, "(%d) (a - 3b)(a - 3b + 3) - 10\n", questions );
						fprintf( fp2, "(%d) (a - 3b + 5)(a - 3b - 2)\n", questions );
						break;	
						case 10 :
						fprintf( fp1, "(%d) x^2 + 2xy + y^2 - 4\n", questions );
						fprintf( fp2, "(%d) (x + y + 2)(x + y - 2)\n", questions );
						break;
						case 11 :
						fprintf( fp1, "(%d) x^2 - 4xy + 4y^2 - 9\n", questions );
						fprintf( fp2, "(%d) (x - 2y + 3)(x - 2y - 3)\n", questions );
						break;
						case 12 :
						fprintf( fp1, "(%d) 4x^2 - 1 - 12xy + 9y^2\n", questions );
						fprintf( fp2, "(%d) (2x - 3y + 1)(2x - 3y - 1)\n", questions );	
						break;
						case 13 :
						fprintf( fp1, "(%d) a - 1 + b(1 - a)\n", questions );
						fprintf( fp2, "(%d) (a - 1)(1 - b)\n", questions );	
						break;
						case 14 :
						fprintf( fp1, "(%d) a^2 + ab - 2b - 4\n", questions );
						fprintf( fp2, "(%d) (a - 2)(a + b + 2)\n", questions );				
						break;
						case 15 :
						fprintf( fp1, "(%d) x^4 + x^2 + 1\n", questions );
						fprintf( fp2, "(%d) (x^2 + x + 1)(x^2 - x + 1)\n", questions );	
						break;		
						case 16 :
						fprintf( fp1, "(%d) x^4 + 4\n", questions );
						fprintf( fp2, "(%d) (x^2 + 2x + 2)(x^2 - 2x + 2)\n", questions );	
						break;	
						case 17 :
						fprintf( fp1, "(%d) x^4 - 3x^2 + 1\n", questions );
						fprintf( fp2, "(%d) (x^2 + x - 1)(x^2 - x - 1)\n", questions );	
						break;
						case 18 :
						fprintf( fp1, "(%d) x^4 + 3x^2 + 4\n", questions );
						fprintf( fp2, "(%d) (x^2 + x + 2)(x^2 - x + 2)\n", questions );	
						break;
						case 19 :
						fprintf( fp1, "(%d) a^3 + a^2 b - a(b^2 + c^2) + bc^2 - b^3\n", questions );
						fprintf( fp2, "(%d) (a - b)(a + b + c)(a + b - c)\n", questions );	
						break;																								
						case 20 :
						fprintf( fp1, "(%d) a^3 + a^2 - 2a - a^2 b - ab + 2b\n", questions );
						fprintf( fp2, "(%d) (a + 2)(a - 1)(a - b)\n", questions );	
						break;
						case 21 :
						fprintf( fp1, "(%d) (a + b)x^2 - 2ax + a - b\n", questions );
						fprintf( fp2, "(%d) (x - 1){(a + b)x - a + b}\n", questions );	
						break;						
						default : break;
					}
					break;
			case 7 :
				RESET7:
				b = rand() % 10 + 1;
				c = ( rand() % 20 + 2 ) * ( 1 - 2 * ( rand() % 2 ) );
				d = rand() % 10 + 1;
				e = ( rand() % 20 + 1 ) * ( 1 - 2 * ( rand() % 2 ) );
				gcd_bc = euclid( b, abs( c ) );
				b /= gcd_bc;
				c /= gcd_bc;
				gcd_de = euclid( d, abs( e ) );
				d /= gcd_de;
				e /= gcd_de;

				a = gcd_bc * gcd_de * ( 1 - 2 * ( rand() % 2 ) ) * ( rand() % 2 + 1 );

				qa = a * b * d;
				qb = a * ( b * e + c * d);
				if(qb > 0) pmqb[0] = '+';
				else if( qb == 0 ) goto RESET7;
				else pmqb[0] = '-';
				qc = a * c * e;
				if( qc > 0 ) pmqc[0] = '+';
				else if( qc == 0 ) break;
				else pmqc[0] = '-';
				if( c >= 0) pmc[0] = '+';
				else pmc[0] = '-';
				if( e >= 0) pme[0] = '+';
				else pme[0] = '-';					
				
				if( qa == 1 ) fprintf( fp1, "(%d) x^2 %c %dxy %c %dy^2 \n", questions, pmqb[0], abs( qb ), pmqc[0], abs( qc ) );
				else if( qa == -1 ) fprintf( fp1, "(%d) -x^2 %c %dxy %c %dy^2 \n", questions, pmqb[0], abs( qb ), pmqc[0], abs( qc ) );
				else fprintf( fp1, "(%d) %dx^2 %c %dxy %c %dy^2\n", questions, qa, pmqb[0], abs( qb ), pmqc[0], abs( qc ) );
				// fprintf( fp2, "(%d) %d(%dx %c %dy)(%dx %c %dy)\n", questions, a, b, pmc[0], abs( c ), d, pme[0], abs( e ) );

				if( abs( a ) != 1 )fprintf( fp2, "(%d) %d", questions , a );
				else if( a == -1 )fprintf( fp2, "(%d) -", questions );
				else fprintf( fp2, "(%d) ", questions );

				if( abs( b ) != 1 )fprintf( fp2, "(%dx ", b );
				else if( b == -1 )fprintf( fp2, "(-x ");
				else fprintf( fp2, "(x");

				if( abs( c ) != 1 )fprintf( fp2, "%c %dy)(", pmc[0], abs ( c ) );
				else fprintf( fp2, "%c y)(", pmc[0] );

				if( abs( d ) != 1 )fprintf( fp2, "%dx ", d );
				else if( d == -1 )fprintf( fp2, "-x ");
				else fprintf( fp2, "x ");				

				if( abs( e ) != 1 ) fprintf( fp2, "%c %dy)\n", pme[0], abs ( e ) );
				else fprintf( fp2, "%c y)\n", pme[0] );
				break;	

			default : break;
		}
		fprintf( fp1, "\n" );
		fprintf( fp2, "\n" );
		questions++;
	}

	fclose( fp1 );
	fclose( fp2 );
	return 0;
}