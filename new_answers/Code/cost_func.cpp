/*
 * cost_func.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: Shayan Taheri (A01956093)
 */

 // Specifying the libraries according to the functions and specifications.

 #include <iostream>
 #include <limits>
 #include <algorithm>
 #include <string>
 #include <cmath>
 #include <fstream>
 using namespace std;

 /* Defining the Cost function. It is needed to consider 4 inputs for this function. Also, regarding the fact that
    the designed function needs 3 functions in its structure (according to my design) and it is out of the main function,
    I defined a class with 3 functions as its elements to make a nesting call function. */

 float cost(char ex1[39], char op[20], float area[20], float ratio[20])
 {

 // Defining the class with 3 needed functions !

	class local
	{
		public:

		// Function "maxn" gives the maximum of two float numbers.

		static float maxn (float a, float b) {
			if (a > b)
				return a;
			else
				return b;
		}

		// Function "minn" gives the minimum of two float numbers.

		static float minn (float c, float d) {
			if (c < d)
				return c;
			else
				return d;
		}

		/* Function "check" is for checking procedure of the results of two leaves (Children). It means that this functions will check
		   the overlapping state of four achieved results. In 'H' operation, a1, a2, a3, and a4 are for heights and b1, b2, b3, and b4 are
		   for widths and vice versa. */

		static void check (float& a1, float& a2, float& a3, float& a4, float& b1, float& b2, float& b3, float& b4) {
		if ((b1 <= b2) && (b1 <= b3) && (b1 <= b4)) {
			if ((a3 <= a2) && (a3 <= a4)) {
				a2 = a3;
				b2 = b3; }
			if ((a4 <= a2) && (a4 <= a3)) {
				a2 = a4;
				b2 = b4; }}
		if ((b2 <= b1) && (b2 <= b3) && (b2 <= b4)) {
			if ((a3 <= a1) && (a3 <= a4)) {
				a1 = a3;
				b1 = b3; }
			if ((a4 <= a1) && (a4 <= a3)) {
				a1 = a4;
				b1 = b4; }}
		if ((b3 <= b1) && (b3 <= b2) && (b3 <= b4)) {
			if ((a1 <= a2) && (a1 <= a4)) {
				a2 = a3;
				b2 = b3; }
			if ((a2 <= a1) && (a2 <= a4)) {
				a1 = a3;
				b1 = b3; }
			if ((a4 <= a1) && (a4 <= a2)) {
				a1 = a3;
				b1 = b3;
				a2 = a4;
				b2 = b4; }}
		if ((b4 <= b1) && (b4 <= b2) && (b4 <= b3)) {
			if ((a1 <= a2) && (a1 <= a3)) {
				a2 = a4;
				b2 = b4; }
			if ((a2 <= a1) && (a2 <= a3)) {
				a1 = a4;
				b1 = b4; }
			if ((a3 <= a1) && (a3 <= a2)) {
				a1 = a3;
				b1 = b3;
				a2 = a4;
				b2 = b4; }}
		}

	};

	// Start point for defining the local variables of the cost function.

	/* In this code, I have designed and coded the cost function with the following algorithm.
	   We can consider every two operands and an operator from the left of the NPE as a subset (subtree) of
	   normalized polish expression and replace it with a new operand such as 'x'.
	   So, if we have an operator ('H' or 'V') in location 'i' then our operands should be in
	   locations 'i-1' and 'i-2'. */

	/* After each operation ('H' or 'V'), we would have four results and we can keep two of them according
	   to the overlapping ("check" function) and replace the two other ones with the future new results.
	   But, in the last operation, there would be four results and even after the "check" function,
	   we should have 4 available spaces for them. So, we should consider 40 = (2 * 19) + 2 spaces for
	   new height and width arrays: "h_comp" and "w_comp" */

	char op2 = {'x'};
	float h[20];
	float w[20];
	float h_comp[40];
	float w_comp[40];
	float rt1 = 0.0;
	float rt2 = 0.0;
	float rt3 = 0.0;
	float rt4 = 0.0;
	float res1 = 0.0;
	float res2 = 0.0;
	float result = 0.0;
	float h1 = 0.0;
	float h2 = 0.0;
	float w1 = 0.0;
	float w2 = 0.0;
	int c = 0;
	int p = 38;
	int j = 0;
	int k = 0;
	char ex2[39];
	int con1 = 0;
	int con2 = 0;
	int con3 = 0;
	int con4 = 0;
	char val1, val2;
	int i = 0;

	// Obtaining height and width of modules according to their area (= h * w) and ratio (= h / w).

	for (int q = 0; q <= 19; q++) {
		w[q] = sqrt (area[q] / ratio [q]);
		h[q] = area[q] / w[q];}

	for (int yo = 0; yo <= 38; yo++) {
		ex2[yo] = 0;}

	for (int eo = 0; eo <= 39; eo++) {

		h_comp[eo] = 0;
		w_comp[eo] = 0;
	}

	/* Start point for checking each element of NPE for finding an operator ('H' or 'V') and then applying
	   the explained algorithm. */

	for (; i <= 38; i++) {

		// If the element 'i' of the NPE is equal to 'V'.

		if ((ex1[i] == 'V') && (c <= 36)) {

			for (; j <= 19; j++) {
			if ((ex1[i-1] == op[j])) {
				val1 = op[j];
				h1 = h[j];
				w1 = w[j];
				j = 20;
			}}

			for (; k <= 19; k++) {
			if ((ex1[i-2] == op[k])) {
				val2 = op[k];
				h2 = h[k];
				w2 = w[k];
				k = 20;
			}}

		// If both of the elements 'i-1' and 'i-2' are in the operands.

		if ((ex1[i-1] == val1) && (ex1[i-2] == val2)) {
			w_comp[c] = h1 + h2;
			w_comp[c+1] = w1 + w2;
			w_comp[c+2] = h1 + w2;
			w_comp[c+3] = w1 + h2;
			h_comp[c] = local::maxn (w1, w2);
			h_comp[c+1] = local::maxn (h1, h2);
			h_comp[c+2] = local::maxn (w1, h2);
			h_comp[c+3] = local::maxn (h1, w2);
			local::check (w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3], h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3]);
			con1 = 1;}

		// If the element 'i-2' is in expression and element 'i-1' is a new operand (= 'x').

		if ((ex1[i-2] == val2) && (ex1[i-1] == op2)) {
			w_comp[c] = h2 + w_comp[c-2];
			w_comp[c+1] = w2 + w_comp[c-2];
			w_comp[c+2] = h2 + w_comp[c-1];
			w_comp[c+3] = w2 + w_comp[c-1];
			h_comp[c] = local::maxn (w2, h_comp[c-2]);
			h_comp[c+1] = local::maxn (h2, h_comp[c-2]);
			h_comp[c+2] = local::maxn (w2, h_comp[c-1]);
			h_comp[c+3] = local::maxn (h2, h_comp[c-1]);
			local::check (w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3], h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3]);
			con2 = 1;}

		// If the element 'i-1' is in expression and element 'i-2' is a new operand (= 'x').

		if ((ex1[i-1] == val1) && (ex1[i-2] == op2)) {
			w_comp[c] = h1 + w_comp[c-2];
			w_comp[c+1] = w1 + w_comp[c-2];
			w_comp[c+2] = h1 + w_comp[c-1];
			w_comp[c+3] = w1 + w_comp[c-1];
			h_comp[c] = local::maxn (w1, h_comp[c-2]);
			h_comp[c+1] = local::maxn (h1, h_comp[c-2]);
			h_comp[c+2] = local::maxn (w1, h_comp[c-1]);
			h_comp[c+3] = local::maxn (h1, h_comp[c-1]);
			local::check (w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3], h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3]);
			con3 = 1;}

		// If both of the elements 'i-1' and 'i-2' are new operands (each of them = 'x').

		if ((ex1[i-1] == op2) && (ex1[i-2] == op2)) {
			w_comp[c] = w_comp[c-1] + w_comp[c-3];
			w_comp[c+1] = w_comp[c-1] + w_comp[c-4];
			w_comp[c+2] = w_comp[c-2] + w_comp[c-3];
			w_comp[c+3] = w_comp[c-2] + w_comp[c-4];
			h_comp[c] = local::maxn (h_comp[c-1], h_comp[c-3]);
			h_comp[c+1] = local::maxn (h_comp[c-1], h_comp[c-4]);
			h_comp[c+2] = local::maxn (h_comp[c-2], h_comp[c-3]);
			h_comp[c+3] = local::maxn (h_comp[c-2], h_comp[c-4]);
			local::check (w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3], h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3]);
			con4 = 1;}

		/* We can assign a 'z' character or any other character (except the initial operands and 'x') to
		   the last two cells of the expression each time to don't consider them in the next iteration again ! */

		// Reconstructing the new normalized polish expression according to the new situation :

		if ((con1 == 1) || (con2 == 1) || (con3 == 1) || (con4 == 1))
		{

		if (p > 1) {
		ex1[i-2] = 'x';
		for (int s = 0; s <= 37-i; s++) {
		ex2[s] = ex1[i+1+s]; }
		for (int v = 0; v <= 37-i; v++) {
		ex1[i-1+v] = ex2[v];}
		ex1[p] = 'z';
		ex1[p-1] = 'z';
		p = p - 2;
		i = 0;
		j = 0;
		k = 0;
		c = c + 2;
		con1 = 0;
		con2 = 0;
		con3 = 0;
		con4 = 0;}
		if (p < 1) {
		i = 39;}

		}

		}

		// The following procedure (ex1[i] = 'H') is approximately the same as the previous procedure (ex1[i] = 'V') :

		if ((ex1[i] == 'H') && (c <= 36)) {

		for (; j <= 19; j++) {
		if ((ex1[i-1] == op[j])) {
			val1 = op[j];
			h1 = h[j];
			w1 = w[j];
			j = 20;
		}}

		for (; k <= 19; k++) {
		if ((ex1[i-2] == op[k])) {
			val2 = op[k];
			h2 = h[k];
			w2 = w[k];
			k = 20;
		}}


		if ((ex1[i-1] == val1) && (ex1[i-2] == val2)) {
			h_comp[c] = h1 + h2;
			h_comp[c+1] = w1 + w2;
			h_comp[c+2] = h1 + w2;
			h_comp[c+3] = w1 + h2;
			w_comp[c] = local::maxn (w1, w2);
			w_comp[c+1] = local::maxn (h1, h2);
			w_comp[c+2] = local::maxn (w1, h2);
			w_comp[c+3] = local::maxn (h1, w2);
			local::check (h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3], w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3]);
			con1 = 1;}

		if ((ex1[i-2] == val2) && (ex1[i-1] == op2)) {
			h_comp[c] = h2 + h_comp[c-2];
			h_comp[c+1] = w2 + h_comp[c-2];
			h_comp[c+2] = h2 + h_comp[c-1];
			h_comp[c+3] = w2 + h_comp[c-1];
			w_comp[c] = local::maxn (w2, w_comp[c-2]);
			w_comp[c+1] = local::maxn (h2, w_comp[c-2]);
			w_comp[c+2] = local::maxn (w2, w_comp[c-1]);
			w_comp[c+3] = local::maxn (h2, w_comp[c-1]);
			local::check (h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3], w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3]);
			con2 = 1;}

		if ((ex1[i-1] == val1) && (ex1[i-2] == op2)) {
			h_comp[c] = h1 + h_comp[c-2];
			h_comp[c+1] = w1 + h_comp[c-2];
			h_comp[c+2] = h1 + h_comp[c-1];
			h_comp[c+3] = w1 + h_comp[c-1];
			w_comp[c] = local::maxn (w1, w_comp[c-2]);
			w_comp[c+1] = local::maxn (h1, w_comp[c-2]);
			w_comp[c+2] = local::maxn (w1, w_comp[c-1]);
			w_comp[c+3] = local::maxn (h1, w_comp[c-1]);
			local::check (h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3], w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3]);
			con3 = 1;}

		if ((ex1[i-1] == op2) && (ex1[i-2] == op2)) {
			h_comp[c] = h_comp[c-1] + h_comp[c-3];
			h_comp[c+1] = h_comp[c-1] + h_comp[c-4];
			h_comp[c+2] = h_comp[c-2] + h_comp[c-3];
			h_comp[c+3] = h_comp[c-2] + h_comp[c-4];
			w_comp[c] = local::maxn (w_comp[c-1], w_comp[c-3]);
			w_comp[c+1] = local::maxn (w_comp[c-1], w_comp[c-4]);
			w_comp[c+2] = local::maxn (w_comp[c-2], w_comp[c-3]);
			w_comp[c+3] = local::maxn (w_comp[c-2], w_comp[c-4]);
			local::check (h_comp[c], h_comp[c+1], h_comp[c+2], h_comp[c+3], w_comp[c], w_comp[c+1], w_comp[c+2], w_comp[c+3]);
			con4 = 1;}

		if ((con1 == 1) || (con2 == 1) || (con3 == 1) || (con4 == 1))
		{

		if (p > 1) {
		ex1[i-2] = 'x';
		for (int s = 0; s <= 37-i; s++) {
		ex2[s] = ex1[i+1+s]; }
		for (int v = 0; v <= 37-i; v++) {
		ex1[i-1+v] = ex2[v];}
		ex1[p] = 'z';
		ex1[p-1] = 'z';
		p = p - 2;
		i = 0;
		j = 0;
		k = 0;
		c = c + 2;
		con1 = 0;
		con2 = 0;
		con3 = 0;
		con4 = 0;}
		if (p < 1) {
		i = 39;}

		}

		}

	}

	// Checking the minimum size of the area for final result of the cost function:

	rt1 = h_comp[36] * w_comp[36];
	rt2 = h_comp[37] * w_comp[37];
	res1 = local::minn (rt1, rt2);

	rt3 = h_comp[38] * w_comp[38];
	rt4 = h_comp[39] * w_comp[39];
	res2 = local::minn (rt1, rt2);

	result = local::minn (res1, res2);

	return result;

}


int main()
	{
		// Defining the normalized polish expression (EXPRESSION) and the local variables of "main" function.

		// *** PLEASE SET "EXPRESSION[39]" TO ONE OF THE Normalized Polish Expression Topologies : ***

		float AREA[20];
		float RATIO[20];
		char OPERANDS[20];
		char EXPRESSION[39] = {'2','1','3','5','4','6','H','7','V','H','V','a','8','V','9','H','c','V','H','g','H','i','b','d','H','k','V','H','f','e','H','V','l','H','V','j','H','V','H'};
		float cost_result = 0.0;

		/* The Normalized Polish Expression Topologies :

		   a. {'1','2','V','3','V','4','V','5','V','6','V','7','V','8','V','9','V','a','V','b','V','c','V','d','V','e','V','f','V','g','V','i','V','j','V','k','V','l','V'}
		   b. {'1','2','H','3','H','4','H','5','H','6','H','7','H','8','H','9','H','a','H','b','H','c','H','d','H','e','H','f','H','g','H','i','H','j','H','k','H','l','H'}
		   c. {'2','1','3','5','4','6','H','7','V','H','V','a','8','V','9','H','c','V','H','g','H','i','b','d','H','k','V','H','f','e','H','V','l','H','V','j','H','V','H'}

		*/

		// Reading the input file and assigning its content to the equivalent arrays :

		ifstream fp ("input_file.txt");
		if (fp.is_open())
		{
			while ( !fp.eof() )
			{
				for (int o = 0; o <= 19; o++) {
					fp >> OPERANDS[o];
					fp >> AREA[o];
					fp >> RATIO[o];}
			}
		}

		// Outputting the Topology (NPE).

		cout << "The Topology (NPE) is: \n";

		for (int yw = 0; yw <= 38; yw++) {

			cout << EXPRESSION[yw] << " ";
		}

		// Invoking the Cost Function and assigning its return value to "cost_result" variable :

		cost_result = cost (EXPRESSION, OPERANDS, AREA, RATIO);

		// Outputting the Cost of Floorplan (area).

		cout << "\n\nThe Cost of Floorplan is: \n" << cost_result << "\n";

			return 0;

		}
