# MAP401
## Compte rendu Tache 6

### Partie 1
___
Le code source de la fonction  de calcul de la distance 
point-segment est dans le fichier [vectors.c](vectors.c)

Le programme test est [vectorTest.c](vectorTest.c) :
`make vectorTest`

Le jeu de test couvrant tous les cas est dans le fichier 
[vector.test.c](vector.test.c) :
`make vector.test`

### Partie 2
___

<table>
    <tr>
        <th>Fichiers</th>
        <th>Nombre de contours</th>
        <th>Nombre de segments avant simplification</th>
        <th colspan="2">Nombre de segments après simplification</th>
    </tr>
    <tr>
        <th></th>
        <th></th>
        <th></th>
        <th>d = 1</th>
        <th>d = 2</th>
    </tr>
    <tr align="center">
        <td><a href="img/image_poly_tache6.pbm">image_poly_tache6.eps</a></td>
        <td>3</td>
        <td>483</td>
        <td><a href="img/image_poly_tache6_d1.eps">66</a></td>
        <td><a href="img/image_poly_tache6_d2.eps">44</a></td>
    </tr>    
    <tr align="center">
        <td><a href="img/elephant-gotlib.pbm">elephant-gotlib.pbm</a></td>
        <td>313</td>
        <td>115249</td>
        <td><a href="img/elephant-gotlib_d1.eps">13074</a></td>
        <td><a href="img/elephant-gotlib_d2.eps">4137</a></td>
    </tr>   
     <tr align="center">
        <td><a href="img/goudyini-A.pbm">goudyini-A.pbm</a></td>
        <td>258</td>
        <td>73184</td>
        <td><a href="img/goudyini-A_d1.eps">5341</a></td>
        <td><a href="img/goudyini-A_d2.eps">2664</a></td>
    </tr>  
      <tr align="center">
        <td><a href="img/cheval.pbm">cheval.pbm</a></td>
        <td>59</td>
        <td>31941</td>
        <td><a href="img/cheval_d1.eps">3145</a></td>
        <td><a href="img/cheval_d2.eps">1380</a></td>
    </tr>   
     <tr align="center">
        <td><a href="img/papillon2_d2.eps">papillon2.eps</a></td>
        <td>140</td>
        <td>18070</td>
        <td><a href="img/papillon2_d1.eps">1858</a></td>
        <td><a href="img/papillon2_d2.eps">1016</a></td>
    </tr>
</table>​

|:---:|:---:|:---:|:---:|:---:|
|a|b|c| d = 1 | d = 2 |
| [image_poly_tache6.eps](img/image_poly_tache6_d1.eps) | 3 | 483 | 66
| [Charlot.pbm](img/Charlot.pbm) | 34 | 9040 |
| [Pink_Panther.pbm](img/Pink_Panther.pbm) | 38 | 32028 |
| [animaux.pbm](img/animaux.pbm) | 96 | 34396 |
| [damier_4_5_1.pbm](img/damier_4_5_1.pbm) | 4 | 40 |
| [deux-des.pbm](img/damier_4_5_1.pbm) | 38 | 11124 |
| [dessin-delius.pbm](img/damier_4_5_1.pbm) | 815 | 110928 |
| [gai-luron.pbm](img/damier_4_5_1.pbm) | 375 | 87636 |
| [papillon2.pbm](img/papillon2.pbm) | 140 | 18212 |