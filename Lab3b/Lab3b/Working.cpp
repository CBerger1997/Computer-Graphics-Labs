//Task 5 – calculate the combined transformation matrix M

/*	
	T = ( 1, 0, 0, 0.5,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1 )

	R = ( 0,-1,	0, 0,
		  1,⁡ 0,	0, 0,
		  0, 0,	1, 0,
		  0, 0,	0, 1 )

	Dot Product:
	
	TR = (	1*0 + 0*-1 + 0*0 + 0.5*0 = 0, 1*-1 + 0*0 + 0*0 + 0.5*0 = -1, 1*0 + 0*0 + 0*1 + 0.5*0 == 0, 1*0 + 0*0 + 0*0 + 0.5*1 = 0.5,
			1, 0, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)

	M = (	0,-1, 0, 0.5,
			1, 0, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)
*/ 
//Task 6 - Calculate the new vertex position after rotating and translating, which is Mv
/*
	M = (	0,-1, 0, 0.5,
			1, 0, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)
			
	v = (	0,
			0.25,
			0,
			1	)

	Mv = (	0*0 + 0.25*-1 + 0*0 + 1*0.5 = 0.25,
			0*1 + 0.25*0 + 0*0 + 1*0	= 0,
			0*0 + 0.25*0 + 0*1 + 1*0	= 0,
			0*0 + 0*0.25 + 0*0 + 1*1	= 1 )
*/
//Task 7 – calculate the combined transformation matrix M
/*
	R = ( 0,-1, 0, 0,
		  1, ⁡0, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1 )

	T = ( 1, 0, 0, 0.5,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1 )

	RT = (	0,-1, 0, 0,
			1, 0, 0, 0.5,
			0, 0, 1, 0,
			0, 0, 0, 1 )
*/
//Task 8 - Calculate the new vertex position after translating and then rotating, which is Mv
/*

	M = ( 0,-1, 0, 0,
		  1, 0, 0, 0.5,
		  0, 0, 1, 0,
		  0, 0, 0, 1 )

	V = (	0,
			0.25,
			0
			1	)

	Mv = (	-0.25,
			0.5,
			0,
			1	)
*/
