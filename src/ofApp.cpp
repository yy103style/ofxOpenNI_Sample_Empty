#include "ofApp.h"
#define NUMA 10 //円の数を表す定数NUMを1000と定義

//float loc_x[NUMA]; //円のx座標
//float loc_y[NUMA]; //円のy座標
//float speed_x[NUMA]; //x軸方向のスピード
//float speed_y[NUMA]; //y軸方向のスピード
//float radius[NUMA]; //円の半径
//int red[NUMA]; //Red成分
//int green[NUMA]; //Green成分
//int blue[NUMA]; //Blue成分
bool mouse_pressed; //マウスはクリックされているか?
int gather_x,gather_y;
int temp;

#define NUM 2000
#define DISTANCE 1000000000
int x[NUM];
int y[NUM];
int z[NUM];
int size[NUM];
bool change;

//--------------------------------------------------------------
void ofApp::setup() {
    //  window
    ofBackground(0, 0,0);
    ofSetWindowShape(640, 480);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    //  setup ofxOpenNI
    kinect.setup();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addImageGenerator();     //  required for RGB image
    kinect.addDepthGenerator();     //  required for depth image
    kinect.addHandsGenerator();      //  required for hand tracking
    kinect.addAllHandFocusGestures();
    kinect.setMaxNumHands(2);       //  max num of skeleton to track
    //  start kinect
    kinect.start();
    
    /*beat[0].loadSound("cymbals_1.mp3");
    beat[0].setLoop(false);
    beat[1].loadSound("bass_1.mp3");
    beat[1].setLoop(false);
    beat[2].loadSound("bass_2.mp3");
    beat[2].setLoop(false);
    beat[3].loadSound("bass_3.mp3");
    beat[3].setLoop(false);
    beat[4].loadSound("tom_1.mp3");
    beat[4].setLoop(false);
    beat[5].loadSound("drum_1.mp3");
    beat[5].setLoop(false);
    beat[6].loadSound("drum_2.mp3");
    beat[6].setLoop(false);
    beat[7].loadSound("drum_3.mp3");
    beat[7].setLoop(false);
    beat[8].loadSound("hat_1.mp3");
    beat[8].setLoop(false);
    beat[9].loadSound("b_005.mp3");*/
    beat[0].setLoop(false);
    beat[0].loadSound("nc30614.wav");
    beat[1].setLoop(false);
    beat[1].loadSound("b_004.mp3");
    beat[2].setLoop(false);
    beat[2].loadSound("tom_1.mp3");
    beat[3].setLoop(false);
    beat[3].loadSound("b_036.mp3");
    beat[4].setLoop(false);
    beat[4].loadSound("b_039.mp3");
    beat[5].setLoop(false);
    beat[5].loadSound("b_043.mp3");
    beat[6].setLoop(false);
    beat[6].loadSound("b_052.mp3");
    beat[7].setLoop(false);
    beat[7].loadSound("b_108.mp3");
    beat[11].setLoop(false);
    beat[11].loadSound("b_038.mp3");
    beat[9].setLoop(false);
    beat[9].loadSound("b_068.mp3");
    beat[10].setLoop(false);
    beat[10].loadSound("b_001.mp3");
     /*beat[21].setLoop(false);
     beat[21].loadSound("");*/
     beat[12].setLoop(false);
     beat[12].loadSound("drum_1.mp3");
     /*beat[22].setLoop(false);
     beat[23].loadSound("");
     beat[23].setLoop(false);
     beat[24].loadSound("");
     beat[24].setLoop(false);
     beat[25].loadSound("b_001.mp3");
     beat[25].setLoop(false);*/
    
    
    ofSetCircleResolution(90);
    
    
    ofBackground(0, 0, 0); //背景色の設定
    ofSetFrameRate(60); //フレームレートの設定
    ofSetCircleResolution(64); //円の解像度設定
    ofEnableAlphaBlending(); //アルファチャンネルを有効に
    
    mouse_pressed = false; //マウス状態を「クリックされていない」に
    
//    //NUMの数だけ初期値の生成を繰り返す
//    for(int i = 0; i < NUM; i++){
//        loc_x[i] = ofRandom(0, ofGetWidth()); //円のx座標初期位置
//        loc_y[i] = ofRandom(0, ofGetHeight()); //円のy座標初期位置
//        speed_x[i] = ofRandom(-5, 5); //x軸方向スピード初期値
//        speed_y[i] = ofRandom(-5, 5); //y軸方向スピード初期値
//        radius[i] = ofRandom(4, 40); //円の半径を設定
//        red[i] = ofRandom(0, 255); //Red成分を設定
//        green[i] = ofRandom(0, 255); //Green成分を設定
//        blue[i] = ofRandom(0, 255); //Blue成分を設定
//    }
    
    ofBackground(10, 10, 90);
    
    cameraRotation.set(0);//cameraRotationは三次元ベクトル(スカラーがここではセットされている)
    zoom = -500;//zoomをz軸方向の基準座標系として使う
    zoomTarget = 200;//keyEventでカメラを近づけたりする際にzoomに影響を及ぼす
    
    ofDisableArbTex();
    ofEnableAlphaBlending();
    ofToggleFullscreen();
    ofSetFrameRate(100);
    change=false;
    
    //locating boxes
    for(int i=0;i<NUM;i++){
        x[i] = ofRandom(-ofGetWidth(),ofGetWidth());
        y[i] = ofRandom(-ofGetWidth(),ofGetWidth());
        z[i] = ofRandom(-ofGetWidth(),ofGetWidth());
        size[i]=ofRandom(5,12);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    //NUMの数だけ座標の更新を繰り返す
//    for(int i = 0; i < NUM; i++){
    
        //マウスの現在位置からスピードを//もしマウスがクリックされていたらマウスに集ってくる
//        if(mouse_pressed){
//            //マウスの現在位置から円のスピードを再計算
//            speed_x[i] = (gather_x - loc_x[i]) / 8.0; //マウスのx座標と円のx座標の距離の1/8だけ接近
//            speed_y[i] = (gather_y - loc_y[i]) / 8.0; //マウスのy座標と円のy座標の距離の1/8だけ接近
//        }else if((int)ofGetElapsedTimef()%10==0){
//            speed_x[i] = ofRandom(-5, 5); //x軸方向スピード初期値
//            speed_y[i] = ofRandom(-5, 5); //y軸方向スピード初期値
//        }
        
//        loc_x[i] = loc_x[i] + speed_x[i]; //円のx座標を更新
//        loc_y[i] = loc_y[i] + speed_y[i]; //円のy座標を更新
//        
//        //円の跳ね返り条件
//        if(loc_x[i] < 0){
//            speed_x[i] = speed_x[i] * -1;
//        }
//        if(loc_x[i] > ofGetWidth()){
//            speed_x[i] = speed_x[i] * -1;
//        }
//        if(loc_y[i] < 0){
//            speed_y[i] = speed_y[i] * -1;
//        }
//        if(loc_y[i] > ofGetHeight()){
//            speed_y[i] = speed_y[i] * -1;
//        }
//    }
    temp+=5;
    if(temp>255){
        temp=0;
    }
    
    zoomTarget=gather_x;
    
    // move the camera around
    float mx = (float)gather_x/(float)ofGetWidth();
    float my = (float)gather_y/(float)ofGetHeight();
    ofVec3f des(mx * 360.0, my * 360.0, 0);
    cameraRotation += (des-cameraRotation) * 0.05;//三次元ベクトルcameraRotationに現在地に依存する三次元ベクトルの影響を及ぼす
    zoom += (zoomTarget - zoom) * 0.05;
    
    if((gather_x-ofGetWidth()/2<=0)&&(change==false)){
        change=true;
    }else if((gather_x-ofGetWidth()/2>0)&&(change==true)){
        change=false;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    mouse_pressed=false;
    ofSetColor(100,100,100,150);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    
    kinect.drawImage(0,0,ofGetWidth(),ofGetHeight());
    
    
    //------------------------------------------------------
    ofSetColor(255);
    
    ofPushMatrix();
    
    if(change==false){
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 1200-zoom);
        ofRotate(cameraRotation.x, 0, 1, 0);//横回転(mouseXに連動)
    }else if(change==true){
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom-50);
        ofRotate(cameraRotation.x, 0, 1, 0);//横回転(mouseXに連動)
    }
    
    
    //ofRotate(cameraRotation.x, 0, 1, 0);//横回転(mouseXに連動)
    ofRotate(cameraRotation.y, 1, 0, 0);//縦回転(mouseYに連動)
    //ofRotate(cameraRotation.y, 0, 0, 1);//円回転(mouseYに連動)
    //ofNoFill();
    //ofDrawSphere(0,0,20);
    
    ofSetColor(250,0,0);
    //ofLine(-1*DISTANCE, 0,0, DISTANCE, 0,0);//x軸
    //ofLine(0, -1*DISTANCE, 0,0, DISTANCE,0);//y軸
    //ofLine(0, 0, -1*DISTANCE,0, 0,DISTANCE);//z軸
    
    float hue = fmodf(ofGetElapsedTimef()*10,255);//経過時間のパラメータから255を法としたmodを取る
    
    //ofNoFill();
    for(int i=0;i<NUM;i++){
        ofTranslate(x[i], y[i],z[i]);
        // the range of each of the arguments here is 0..255 so we map i and j to that range.
        c.setHsb( hue, ofRandom(150,255), ofRandom(100,205) );
        //(色相,彩度,輝度)
        
        // assign the color and draw a rectangle
        ofSetColor( c );
        
        ofDrawBox(size[i]);
        ofTranslate(-x[i], -y[i],-z[i]);
    }
    
    ofPopMatrix();
    //------------------------------------------------------
//    
//    for(int i = 0; i < NUM; i++){
//        ofSetColor(red[i], green[i], blue[i], 127); //描画色の設定
//        ofFill();
//        ofSetCircleResolution(red[i]%4+2);
//        ofCircle(loc_x[i], loc_y[i], radius[i]);
//        ofNoFill();
//        ofCircle(loc_x[i], loc_y[i], radius[i]*1.1);//円1を描画
//    }
    //ofSetColor(255,255,255);
    
    
    
    ofScale((float)ofGetWidth()/640,(float)ofGetHeight()/400);
    if (kinect.getNumTrackedHands() > 0) {
        int kinect_num = kinect.getNumTrackedHands();
        ofVec3f p[2];
        for(int n =0;n<kinect.getNumTrackedHands();n++){
            ofxOpenNIHand hand = kinect.getTrackedHand(n);
            ofVec3f q = hand.getPosition();
            ofFill();
            ofSetColor(90,90,90,270);
            ofSetCircleResolution(90);
            ofCircle(q.x, q.y, 10);
            p[n].x=q.x;
            p[n].y=q.y;
        }
        
        for(int n =0;n<kinect.getNumTrackedHands();n++){
             ofSetColor(255);//ボタンの色
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(550, 250, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(550, 250, 30);
            if (ofDist(550,250,p[n].x,p[n].y)<35) {
                beat[0].play();
                //beat[0].setVolume(10.0f);
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(150, 50, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(150, 50, 30);
            if (ofDist(150,50,p[n].x,p[n].y)<35) {
                beat[1].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(250, 50, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(250, 50, 30);
            if (ofDist(250,50,p[n].x,p[n].y)<35) {
                beat[2].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(350, 50, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(350, 50, 30);
            if (ofDist(350,50,p[n].x,p[n].y)<35) {
                beat[3].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(450, 50, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(450, 50, 30);
            if (ofDist(450,50,p[n].x,p[n].y)<35) {
                beat[4].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(550, 150, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(550, 150, 30);
            if (ofDist(550,150,p[n].x,p[n].y)<35) {
                beat[5].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(50, 150, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(50, 150, 30);
            if (ofDist(50,150,p[n].x,p[n].y)<35) {
                beat[6].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(50, 250, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(50, 250, 30);
            if (ofDist(50,250,p[n].x,p[n].y)<35) {
                beat[7].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            /*ofSetCircleResolution(6);
             ofNoFill();
             ofCircle(50, 350, 35);
             ofFill();
             ofSetCircleResolution(3);
             ofCircle(50, 350, 30);
             if (ofDist(50,350,p[n].x,p[n].y)<35) {
             beat[8].play();
             ofSetColor(ofRandom(255));
             mouse_pressed=true;
             }*/
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(150, 350, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(150, 350, 30);
            if (ofDist(150,350,p[n].x,p[n].y)<35) {
                beat[9].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(250, 350, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(250, 350, 30);
            if (ofDist(250,350,p[n].x,p[n].y)<35) {
                beat[10].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(350, 350, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(350, 350, 30);
            if (ofDist(350,350,p[n].x,p[n].y)<35) {
                beat[11].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
                
            }
            ofSetCircleResolution(6);
            ofNoFill();
            ofCircle(450, 350, 35);
            ofFill();
            ofSetCircleResolution(3);
            ofCircle(450, 350, 30);
            if (ofDist(450,350,p[n].x,p[n].y)<35) {
                beat[12].play();
                ofSetColor(ofRandom(255));
                mouse_pressed=true;
            }

        }
        
        gather_x=p[0].x;
        gather_y=p[0].y;
        
    }
    
    //NUMの数だけ円を描画する
    /*
     ofColor c1,c2 ;
     c1.set(0);
     c2.set(temp);
     ofTranslate(0, -500);
     ofBackgroundGradient(c2, c1);
     ofTranslate(0, 500);
     */


}
//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
            case ' ':
            beat[0].play();
            break;
            
    }
    if (key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_pressed = true; //マウスが押されている状態に
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouse_pressed = false; //マウスが押されていない状態に
    
//    //円のスピードを再初期化
//    for(int i = 0; i < NUM; i++){
//        speed_x[i] = ofRandom(-5, 5); //x軸方向スピード初期値
//        speed_y[i] = ofRandom(-5, 5); //y軸方向スピード初期値
//    }

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}