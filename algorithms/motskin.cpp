// N\'umeros Motskin //

Formula: 
   - Recursiva: M_(n+1) =  M_n + sum [ i=0; n-1 ] (M_i*M_(n-1-i)) = (2n+3/n+3)M_n + (3n/n+3)M_(n-1)
   - Coeficientes binomiales y N\'umeros de Catalan: sum [i=0; floor(n/2)]( n , 2k ) C_k
   
Aplicaciones:
   - N\'umero de maneras diferentes de dibujar cuerdas que no se intersecten enntre n puntos en un circulo.
   - El n\'umero de secuencias de enteros positivos de longitud n-1 en donde el elemento inicial y final sean 1 o 2or 2, y que la diferencia entre dos elementos consecutivos sea -1, 0 o 1.
   - Teniendo el cuadrante superior derecho de un plano, el n\'umero Motzkin de n da el n\'umero de rutas desde la coordena (0,0) hasta la coordenada(n, 0) en n pasos
     si se permite s\'olo moverse a la derecha (arriba,abajo, en frente) pero se prohibe que se baje del eje y=0.
