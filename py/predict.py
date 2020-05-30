import segmentation_models as sm
import keras
from cv2 import cv2
import numpy as np
from keras.models import load_model
import sys
from os import listdir
from PIL import Image as PImage
import scipy.misc
from tqdm import tqdm

LR          = 0.0001
BACKBONE    = sys.argv[3]
CLASSES     = ['tree']
dice_loss   = sm.losses.DiceLoss()
n_classes   = 1 if len(CLASSES) == 1 else (len(CLASSES) + 1)  # case for binary and multiclass segmentation
focal_loss  = sm.losses.BinaryFocalLoss() if n_classes == 1 else sm.losses.CategoricalFocalLoss()
total_loss  = dice_loss + (1 * focal_loss)
metrics     = [sm.metrics.IOUScore(threshold=0.5), sm.metrics.FScore(threshold=0.5)]
optim       = keras.optimizers.Adam(LR)
activation  = 'sigmoid' if n_classes == 1 else 'softmax'

model       = sm.Unet(BACKBONE, classes=n_classes, activation=activation)
model.load_weights('py/Unet_' + BACKBONE +'.h5') # change to input var
model.compile(optim, total_loss, metrics)


def loadImages(path):
    # return array of images
    imagesList = listdir(path)
    loadedImages = []
    i = 0
    print("[PYTHON]: Loading images....")
    for image in tqdm(imagesList):
        img = cv2.imread(path + str(i) + "tmp.png") 
        loadedImages.append(img)
        i = i + 1
    return loadedImages

def writeImages(imgs,path):
    i = 0
    print("[PYTHON]: Writing images....")

    for img in tqdm(imgs):
        cv2.imwrite(path + str(i) + "pred.png",img)
        i = i + 1
    return 0

def predImages(imgs,path):
    pred = []
    i = 0
    print("[PYTHON]: Processing images....")
    for til in tqdm(imgs):
        prediction  = model.predict( np.expand_dims(til,axis=0) )[0]
        cv2.cvtColor(prediction, cv2.CV_8UC1, 255)
        prediction_norm = cv2.normalize(prediction, None, alpha = 0, beta = 255, norm_type = cv2.NORM_MINMAX, dtype = cv2.CV_32F)
        np.array(prediction_norm).astype(int)
        cv2.imwrite(path + str(i) + "pred.png",prediction_norm)
        pred.append(prediction_norm)
        i = i + 1
    return pred

path_in = sys.argv[1]
path_out = sys.argv[2]

tiles = loadImages(path_in)
print("numer of tiles: ",len(tiles))
pred = predImages(tiles,path_out)