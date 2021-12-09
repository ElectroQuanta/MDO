bool Player::loadVideo(string filename) {
    //Load the file and get its framerate
    capture.open(filename);
    if (capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void Player::run()
{
    //Delay because of the framerate
    int delay = (1000/frameRate);
    while(!stop){
	//Stop play if doesn't read a frame
        if (!capture.read(frame))
        {
            stop = true;
        }
	// Attribute the image object all the properties from the video frame captured
        if (frame.channels()== 3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);
        }
	//show the frame
        emit processedImage(img);
        //wait the specific time to respect the framerate of the video
	this->msleep(delay);
    }
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
	//puts image on the widget (in this case on a label)
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size()
                                           Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}
