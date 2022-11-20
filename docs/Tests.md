# Описание тестирующей системы

## Виды программ

### Рукописные фильтры

[apply_filter](../programs/apply_filter.cpp) применяет фильтр к картинке.

```sh
./apply_filter <path_to_picture> <filter_name> <window_size> <path_to_save_result>
```

* `path_to_picture` - Путь к оригиналу

* `filter_name` - одно из названий:[Sort](./Sort.md), [Huang](./Huang.md), [Const](./Const.md)

* `window_size` - размер окна для фильтра (не радиус, а сторона квадрата)

* `path_to_save_result` - Куда сохранить ответ

### Фильтры opencv
[apply_filter](../programs/apply_filter.cpp) применяет фильтры из библиотеки с радиусами от 1 до 99 с шагом 2 к картинке.

```sh
./apply_opencv_filter <path_to_picture> <path_to_save_result>
```

* `path_to_picture` - Путь к оригиналу

* `path_to_save_result` - Куда сохранить ответ

### Тесты

[apply_filter](../programs/apply_filter.cpp) применяет фильтр к картинке много раз и записывает время выполнения в файл.

```sh
./test_filters <path_to_picture> <filter_name> <window_size> <number of tests> <path_to_save_result>
```

* `path_to_picture` - Путь к оригиналу

* `filter_name` - одно из названий:[Sort](./Sort.md), [Huang](./Huang.md), [Const](./Const.md)

* `window_size` - размер окна для фильтра (не радиус, а сторона квадрата)

* `number of tests` - количество запускаемых тестов

* `path_to_save_result` - Куда сохранить ответ

## Анализ выходных данных

[test_time.sh](../tests_results/test_time.sh) - запускает серию эксперементов для всех фильтров и картинок и разного размера окон, сохраняя результаты в папку `time_results` рядом. В ней скрипт [make_datasets.py](../tests_results/time_results/make_datasets.py) собирает из этих результатов `.npy` файлы для более удобной работы (поэтому и на гитхаб будут отправлены только они).

В [process_results](../tests_results/process_results.ipynb) написано получение графиков и некоторые вычисления, на основании которых строятся выводы.

В [plots](../tests_results/plots) лежат все графики, а в [pictures](../pictures/) можно найти директории с полученными изображениями