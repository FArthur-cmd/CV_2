# Вывод к работе

В работе сравниваются три варианта медианного фильтра, подробнее о каждом можно прочесть в соответствующих статьях ([Sort](./Sort.md), [Huang](./Huang.md), [Const](./Const.md)).

## Сравнение результатов алгоритмов

Размер окна 9, картинка кот:

Sort:
![s_1](../pictures/Sort_results/Cat_picture_9.jpeg)
Huang:
![h_1](../pictures/Huang_results/Cat_picture_9.jpeg)
Const:
![c_1](../pictures/Const_results/Cat_picture_9.jpeg)

Размер окна 19, картинка кот:

Sort:
![s_2](../pictures/Sort_results/Cat_picture_19.jpeg)
Huang:
![h_2](../pictures/Huang_results/Cat_picture_19.jpeg)
Const:
![c_2](../pictures/Const_results/Cat_picture_19.jpeg)

Размер окна 49, картинка кот:

Sort:
![s_3](../pictures/Sort_results/Cat_picture_49.jpeg)
Huang:
![h_3](../pictures/Huang_results/Cat_picture_49.jpeg)
Const:
![c_3](../pictures/Const_results/Cat_picture_49.jpeg)

Размер окна 3, картинка пейзаж:

Sort:
![s_4](../pictures/Sort_results/Landscape_3.jpeg)

Huang:
![h_4](../pictures/Huang_results/Landscape_3.jpeg)

Const:
![c_4](../pictures/Const_results/Landscape_3.jpeg)

Размер окна 11, картинка пейзаж:

Sort:
![s_5](../pictures/Sort_results/Landscape_11.jpeg)

Huang:
![h_5](../pictures/Huang_results/Landscape_11.jpeg)

Const:
![c_5](../pictures/Const_results/Landscape_11.jpeg)

Размер окна 19, картинка пейзаж:

Sort:
![s_6](../pictures/Sort_results/Landscape_19.jpeg)

Huang:
![h_6](../pictures/Huang_results/Landscape_19.jpeg)

Const:
![c_6](../pictures/Const_results/Landscape_19.jpeg)

Размер окна 43, картинка пейзаж:

Sort:
![s_7](../pictures/Sort_results/Landscape_43.jpeg)

Huang:
![h_7](../pictures/Huang_results/Landscape_43.jpeg)

Const:
![c_7](../pictures/Const_results/Landscape_43.jpeg)

Размер окна 99, картинка пейзаж:

Sort:
![s_8](../pictures/Sort_results/Landscape_99.jpeg)

Huang:
![h_8](../pictures/Huang_results/Landscape_99.jpeg)

Const:
![c_8](../pictures/Const_results/Landscape_99.jpeg)

**Вывод** Алгоритмы работают одинаково, как и ожидалось.

## Скорость работы алгоритмов

Графики скорости работы для картинки кота:

![1](../tests_results/plots/cat.jpg)
![2](../tests_results/plots/cat_without_sort.jpg)

Графики скорости работы для картинки пейзажа:

![3](../tests_results/plots/landscape.jpg)
![4](../tests_results/plots/landscape_without_sort.jpg)

Оценки памяти и времени можно найти в файлах, посвященных самим алгоритмам ([Sort](./Sort.md), [Huang](./Huang.md), [Const](./Const.md))

Коротко:
* `Sort`
   1. Память: $O ((2R + 1)^2) $
   2. Время: $O(M\cdot N \cdot R^2 \log R)$ 

* `Huang`
   1. Память:$O(D)$
   2. Время: $O(M\cdot N \cdot (R + D))$ 

* `Const`
   1. Память: $O(N \cdot D)$
   2. Время: $O(M\cdot N \cdot D)$ 

## Сравнение с opencv 

Скорость на картинку (не мсек/мегапиксель, а секунд на всю картинку)

|picture|opencv|Sort|Huang|Const|
|-|-|-|-|-|
|landscape| (2.9e-05 - 0.004593)| (0.127096 - 102.173)| (0.061134 - 0.24577)| (0.236478 - 0.34202) | 
|cat| (0.000191 - 0.078716) | (21.4803 - 772.894) | (0.948004 - 2.73701) |  (3.90966 - 4.68232) |

Результат выполнения для кота:
![opencv](../tests_results/plots/opencv_Cat_picture.jpg)

Результат выполнения для пейзажа:
![opencv](../tests_results/plots/opencv_Landscape.jpg)

Результаты работы алгоритма и opencv:

Кот для sort размера 9:
![s_cat](../pictures/Sort_results/Cat_picture_9.jpeg)

Кот для opencv размера 9:
![opencv_cat](../pictures/opencv_results/Cat_picture9.jpeg)


Кот для sort размера 29:
![s_cat](../pictures/Sort_results/Cat_picture_29.jpeg)

Кот для opencv размера 29:
![opencv_cat](../pictures/opencv_results/Cat_picture29.jpeg)

__Вывод для сравнения__

OpenCV значительно быстрее выполняет алгоритм, при этом в начале у нее наблюдается всплеск (медленное выполнение), а затем он переходит на константную асимптотику. Алгоритм работает быстрее, так как в нем много оптимизаций в обращении с памятью. 

Что касается результатов, то для библиотеки и собственной реализации они совпадают.

## Предложене использования алгоритмов

Исходя из графиков Sort является не оптимальным и его использование не поможет ни в одном из случаев.

Если посмотреть на следующий график:

![2](../tests_results/plots/cat_without_sort.jpg)

то можно придти к выводу, что наступит $R\approx 200$, когда `Huang` будет выполняться дольше `Const`.

__Рекомендация__: Если диаметр окна меньше 200, то используем `Huang`, иначе используем `Const`.
