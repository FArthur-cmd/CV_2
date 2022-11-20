# Медианный фильтр основанный на сортировке

## Реализация

Реализация алгоритма находится в файлах [SortMedianFilter.h](../include/Filters/SortMedianFilter.h) и [SortMedianFilter.сpp](../include/Filters/SortMedianFilter.cpp). Для каждого пикселя строится окно диаметром `window_size_`. Для каждого канала массив значений в окне сортируется и берется центральный элемент (медиана). Важно, что в реализации используется паддинг вдоль границ. Если мы запрашиваем пиксель, который находится за границей, то будет выдан пиксель в пределах границы. Аналогичный принцип используется в opencv, если верить документации.

## Результаты

Все результаты можно найти в папке `pictures/Sort_results`. Посмотрим на некоторые из них:

Кот при размере окна равном 9:
![Кот при размере окна равном 9](../pictures/Sort_results/Cat_picture_9.jpeg)

Кот при размере окна равном 19:
![Кот при размере окна равном 19](../pictures/Sort_results/Cat_picture_19.jpeg)

Кот при размере окна равном 29:
![Кот при размере окна равном 29](../pictures/Sort_results/Cat_picture_29.jpeg)

Кот при размере окна равном 59:
![Кот при размере окна равном 59](../pictures/Sort_results/Cat_picture_59.jpeg)

Пейзаж при размере окна 3

![Пейзаж при размере окна 3](../pictures/Sort_results/Landscape_3.jpeg)

Пейзаж при размере окна 11

![Пейзаж при размере окна 11](../pictures/Sort_results/Landscape_11.jpeg)

Пейзаж при размере окна 19

![Пейзаж при размере окна 3](../pictures/Sort_results/Landscape_19.jpeg)

Пейзаж при размере окна 43

![Пейзаж при размере окна 43](../pictures/Sort_results/Landscape_43.jpeg)

Пейзаж при размере окна 99

![Пейзаж при размере окна 99](../pictures/Sort_results/Landscape_99.jpeg)



## Теоретическая оценка асимптотики

Допустим на вход подается изображение размером `M x N` и радиус окна `R` (обращу внимание, что под радиусом понимается половина аргумента используемого в моей реализации). Для каждого пикселя этого изображения используется 3 канала. 

### Оценка времени работы

На каждом шаге обрабатывается суммарно $(2R + 1)^2$ пикселей. Построение окна занимает $O(R^2)$ операций. При этом вызывается сортировка, занимающая $O(R^2 \log R)$ (проведено сокращение констант).

В итоге операций всего $O(M\cdot N \cdot R^2 \log R)$ (слагаемое с $R^2$ входит в эту асимптотику).

### Оценка доп памяти
На каждом шаге требуется $3 \cdot (2R + 1)^2$ ячеек памяти (хранение трех каналов окна). Больше затрат на дополнительную паять нет. После выполнения операций эта память освобождается.

### Итог
Память: $O ((2R + 1)^2) $

Время: $O(M\cdot N \cdot R^2 \log R)$ 

## Фактическая оценка асимптотики

Обратим внимание на графики:

Для кота
![1](../tests_results/plots/cat.jpg)
Для пейзажа
![2](../tests_results/plots/landscape.jpg)

Легко увидеть, что этот алгоритм не самый оптимальный и что его вид похож на теоретическую оценку времени. Чтобы убедиться, что мы были правы, попробуем приблизить результат классом функций из $O(R^2 \log R)$ (так как в случае одинаковых картинок можно считать размер картинки константой и он не участвует в асимптотике).


$$Ax^2 \log x + Bx\log x + C\log x + D x^2 + Ex + H$$
![3](../tests_results/plots/Sort_land_approx_1.jpg)

$$Ax^2 \log x + Bx\log x + C\log x + D x^2 + H$$
![4](../tests_results/plots/Sort_land_approx_2.jpg)

$$Ax^2 \log x + Bx\log x + C\log x + H$$
![4](../tests_results/plots/Sort_land_approx_3.jpg)

$$Ax^2 \log x + Bx\log x + H$$
![5](../tests_results/plots/Sort_land_approx_4.jpg)

$$Ax^2 \log x + H$$
![6](../tests_results/plots/Sort_land_approx_5.jpg)

**Вывод** функции хорошо приближают полученный результат, то есть фактическая асимптотика работы совпала с теоретической.

__Замечание__: Подробние о получении всех графиков можно прочесть [здесь](./Tests.md). А о результатах [здесь](./Results.md).