**RUN-Length en/decoding**<br />
This repo is the implementation of run-length en/decoding method. RLE is a simple lossless data compression method which is very suitable for the data with tons of repeat infromaton.<br />
I first met this compression method is when I was doing airbus-ship-detection project in kaggle. The purpose of this task is to find the ship through the image took by satellite. Due to most of the ships are in the sea, so the most part in image is the information of ocean. Therefore, they use rle encoding method to encode the label of training data.<br />
<br />
Anyway, if we have a data as [10,10,10,10,20,20,20,20,40,40,40,40] which is 12 integers. We can use rle encoding to make this data to [4,10,4,20,4,40] which become only 6 integers. It records the length of repeat data to compression the information. But if the data has a lot of different information like [10,20,30,40,50,60], then the compression result would be [1,10,1,20,1,30,1,40,1,50,1,60] which make the data even bigger.<br />
In image rle encoding, the data has be record to the index of begin position of repeat information and the length of repeat information.<br />
<br />
Here is our original image which we can see a ship in the upper left side of image:<br />
![alt text](https://raw.githubusercontent.com/RayXie29/image_RLE_encoding_decoding/master/imgs/00a9e2ec9.jpg)
<br />
And here is the rle decoded data in "ref/RLE.csv"of the label of original image (segmentation)<br />
90666 2 91434 6 92202 8 92969 9 93737 9 94505 8 95273 8 96041 8 96808 9 97576 9 98344 8 99112 8 99880 8 100647 9 101415 9 102183 8 102951 8 103719 8 104486 9 105254 9 106022 8 106792 6 107564 2 <br />
It makes the label image into 1D array then record where the position of ship in image.<br />
After using the rle-decoding, we got the label image(segmentation)<br />
![alt text](https://raw.githubusercontent.com/RayXie29/image_RLE_encoding_decoding/master/imgs/seg.jpg)
<br />
Then we check the rle-encoding function by encoding this label image into encoding form again.<br />
![alt text](https://raw.githubusercontent.com/RayXie29/image_RLE_encoding_decoding/master/imgs/example.png)
<br />
It works fine! Have a nice day:) <br />
reference:<br />
https://en.wikipedia.org/wiki/Run-length_encoding