#include "algorithm.h"

// Constructor
Algorithms::Algorithms(Blocks* b):data(b){
    selectedAlg = 0;
    working = false;
    sorted = true;
    algcount = alglist.size();

    setdelay(20);

    sortingThread = std::thread(&Algorithms::algo, this);   // Setup the thread
}

// Thread function
void Algorithms::algo(){
    while(true){
        if (!working){
            std::cout << "";        // IDK why but this needs to be here. Prolly the thread requires some task to do.
            continue;
        }

        data->reset_counters();
        data->reset_head();
        switch(selectedAlg){
        case 0:
            Algorithms::check();
            break;
        case 1:
            Algorithms::shuffle();
            break;
        case 2:
            Algorithms::bubblesort();
            Algorithms::check();
            break;
        case 3:
            Algorithms::mergesort();
            //Algorithms::check();
            break;
        case 4:
            Algorithms::quicksort();
            //Algorithms::check();
            break;
        }
        working = false;
    }
}

// Controllers
void Algorithms::start(){
    working = true;
}

void Algorithms::stop(){
    working = false;
    sortingThread.detach();
}

void Algorithms::setalg(int s){
    if (s == -1)
        selectedAlg = (selectedAlg + 1)%algcount;
    else if (s == -2)
        selectedAlg = (selectedAlg - 1)%algcount;
    else
        selectedAlg = s;
    data->reset_head();
    data->reset_counters();
}

void Algorithms::setdelay(int d){
    if (d > 0)
        delay = d;
    else if (d == -1)
        delay += 10;
    else if (d == -2 && delay > 10)
        delay -= 10;
    else if (d == -3)
        delay += 100;
    else if (d == -4 && delay > 100)
        delay -=100;
    else if (d == -5)
        delay += 1000;
    else if (d == -6 && delay > 1000)
        delay -= 1000;
}

// Data Extractors
std::string Algorithms::getalg(){
    return alglist[selectedAlg];
}

// Sorting Algorithms
void Algorithms::check(){
    selectedAlg = 0;
    for (data->head.c = 0; data->head.c < data->amount-1; data->head.c++){
        if (data->cmp(data->head.c, data->head.c+1) != -1){
            std::cout << "ERROR at " << data->head.c << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(20000));
    }
    sorted = (data->amount-1 == data->head.c) ? true : false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::shuffle(){
    std::random_shuffle(data->items.begin(), data->items.end());
    sorted = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::bubblesort(){
    for (int i = 0; i < data->amount; i += 1){
        for (int j = 0; j < data->amount-i-1; j += 1){

            if (data->cmp(j, j+1) == 1){
                data->b_swap(j, j+1);
            }

            std::this_thread::sleep_for(std::chrono::microseconds(delay));
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::mergesort(){
    m_ms(0, data->amount-1);
}
void Algorithms::m_ms(int left, int right){
    if (left>=right) return;
    int mid = (left + right)/2;

    m_ms(left, mid);
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
    m_ms(mid+1, right);

    m_merge(left, mid, right);
}
void Algorithms::m_merge(int left, int mid, int right){
    int left_n = mid - left + 1;
    int right_n = right - mid;      // right - (mid + 1) + 1
    
    // Temporary arrays
    int left_arr[left_n];
    int right_arr[right_n];

    // Copying arrays
    for (int i=0; i<left_n; i++) left_arr[i] = data->operator[](left+i);
    for (int i=0; i<right_n; i++) right_arr[i] = data->operator[](mid+1+i);

    // Pointing ints
    int i = 0;
    int j = 0;
    int k = 0;

    // Writing to data
    while (i<left_n && j<right_n)
    {
        if (left_arr[i] <= right_arr[j]){
            data->operator()(left+k, left_arr[i]);
            i++;
        } else {
            data->operator()(left+k, right_arr[j]);
            j++; 
        }
        k++;
    }
    while (i<left_n){
        data->operator()(left+k, left_arr[i]);
        i++; k++;
    }
    while (j<right_n){
        data->operator()(left+k, right_arr[j]);
        j++; k++;
    }
    

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algorithms::quicksort(){
    q_qs(0, data->amount-1);
}
void Algorithms::q_qs(int low, int high){
    if (low >= high) return;
    int pivot_index = q_fix(low, high);

    q_qs(low, pivot_index-1);
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
    q_qs(pivot_index+1, high);
}
int Algorithms::q_fix(int low, int high){
    int i = low - 1;

    for (int j = low; j<high; j++){
        if (data->cmp(j, high) == -1){
            i++;
            if (i != j) data->b_swap(i, j);
        }
    }

    data->b_swap(i+1, high);
    return i+1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
