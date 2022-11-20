#!/usr/bin/env bash

if [ ! -f "../build/test_filters" ]; then
    cd ../build
    cmake -D NDEBUG=1 ..
    make
    cd ../tests_results
fi

for filter in "Huang" "Const" "Sort"
do
    for picture in "Landscape"
    do
        for window_size in $(seq 3 8 100)
        do
            echo "Test ${filter} ${window_size} ${picture}"
            ../build/test_filters ../pictures/originals/${picture}.jpeg ${filter} ${window_size} 5 ./time_results/${filter}_${window_size}_${picture}
            ../build/apply_filter ../pictures/originals/${picture}.jpeg ${filter} ${window_size} ../pictures/${filter}_results/${picture}_${window_size}.jpeg
        done
    done
done


# Heavy picture
for filter in "Huang" "Const" "Sort"
do
    for picture in "Cat_picture"
    do
        for window_size in $(seq 9 10 60)
        do
            echo "Test ${filter} ${window_size} ${picture}"
            ../build/test_filters ../pictures/originals/${picture}.jpeg ${filter} ${window_size} 5 ./time_results/${filter}_${window_size}_${picture}
            ../build/apply_filter ../pictures/originals/${picture}.jpeg ${filter} ${window_size} ../pictures/${filter}_results/${picture}_${window_size}.jpeg
        done
    done
done

for picture in "Cat_picture" "Landscape"
do
    ../build/apply_opencv_filter ../pictures/originals/${picture}.jpeg ../pictures/opencv_results/${picture}.jpeg > ./time_results/opencv_${picture}
done