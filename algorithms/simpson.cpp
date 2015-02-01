// Regla de Simpson para aproximar integrales //

Formula:
 Integral de a hasta b de f(x) dx = ((b-a)/6) * [f(a) + 4f((a+b)/2) + f(b)]
 
En el caso de que el intervalo [a,b] no sea lo suficientemente pequeño, el error al calcular la integral puede ser muy grande. 
Para ello, se recurre a la fórmula compuesta de Simpson. Se divide el intervalo [a,b] en n subintervalos iguales (con n par), de manera que  x_i = a + ih, 
donde  h = (b-a)/n para i = 0, 1, ..., n.

Aplicando la Regla de Simpson a cada subintervalo  [x_{j-1},x_{j+1}],\  j=1,3,5, ..., n-1,  tenemos:

 Integral de x_{j-1} hasta x_{j+1} de f(x)dx = (x_{j+1}-x_{j-1})/3 * [ f(x_{j-1}) + 4f(x_j)+ f(x_{j+1}) ].

Sumando las integrales de todos los subintervalos, llegamos a que:

 Integral de a hasta b de f(x) dx = (h/3) [ f(x_0)+ 2 * sum_{j=1}^{n/2-1}( f(x_{2j}) ) + 4*sum_{j=1}^{n/2}( f(x_{2j-1})+ f(x_n) ) ]


