# objectcounter

#### video drive (only our members can access with $student_id@handong.edu)
> https://drive.google.com/open?id=15lZPvhesTj4s4xF_Ht_Xu0wryZGDxivu

## ***starting variables for best results (command line inputs)***
--> for codes last updated in 24, Sep, 2019

### *case: 190723_1.mp4*
    "set @upperline=~*2/10, @midline=~*4/10, @belowline=~*6/10 in FrameHandler's constructor."
    inputs : 1 50 50 35 50 120 150 7 0

### *case: 190723_2.mp4*
    "set @upperline=~*1/10, @midline=~*5/10, @belowline=~*9/10 in FrameHandler's constructor."
    inputs : 1 50 50 35 50 120 150 7 0

### *case: 190723_3.mp4*
    "set @upperline=~*1/10, @midline=~*5/10, @belowline=~*9/10 in FrameHandler's constructor."
    inputs : 1 50 50 35 60 100 100 7 0
    
### *case: 190723_4.mp4*
    "set @upperline=~*2/10, @midline=~*5/10, @belowline=~*8/10 in FrameHandler's constructor."
    inputs : 1 50 50 35 50 120 150 3 0


# 9.29
## 함수 세분화하려고 코드 뜯어고쳤음
### 대표적으로 고쳐진 부분 
  프레임에 나타나는 박스가 DetectedObject에서 ROI, DetectedObject 두 개로 나눠짐, ROIs 는 흰 색을 검출했을때 사용되고, 이후 ROIs 를 input으로 Judge 함수 실행된 뒤 output으로 DetectedObject 벡터를 갱신함, 즉 ROIs 벡터는 한 번의 프레임 내에서 detect 알고리즘이 종료되면 바로 제거됨.
  이러한 구현 덕분에 ROI들끼리의 거리를 비교하여 중복을 제거하는 기능은 없어도 됨, 대신 WhiteDetector에서 이미 인식된 white pixel은 제대로 건너뛰어야 하고, Judge에서 원 검출할 때 원이 제대로 하나만 생겨야함
  
> 앞으로 구현해야 할 것
 - Judge.cpp 에서 원 검출기능
 - System.Objs가 존재하는 영역에서는 WhiteDetector가 흰색을 검출하지 않게 하여 중복 방지
 - check_endpoint()
 - Trackbar
 
