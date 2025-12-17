# Vatsal Jaiswal - YOLOv8 Training Script
#
# Hey Vatsal! This script is your starting point for training a YOLOv8 model
# on your custom dataset. Since you appreciate the nitty-gritty details, I've
# added comments explaining the 'why' behind the code.
#
# How it works under the hood:
# 1.  We import the necessary libraries: ultralytics for the YOLO model and torch
#     to intelligently check for a GPU.
# 2.  We load a pre-trained YOLOv8 model ('yolov8n.pt'). This is a key concept
#     called **Transfer Learning**. The model has already been trained on a massive
#     dataset (COCO), so it already knows how to recognize basic features like
#     edges, corners, and textures. We're just fine-tuning the final layers to
#     recognize *your specific* objects. This is way more efficient than training
#     from scratch.
# 3.  We call the `train()` method, passing in our configuration. The most important
#     argument is `data='robo/data.yaml'`, which points to your dataset definition file.
# 4.  The training loop begins:
#     - The model takes a batch of images.
#     - It makes predictions (forward pass).
#     - It compares its predictions to your ground-truth labels.
#     - It calculates a 'loss' value (a measure of how wrong it was).
#     - It uses backpropagation to adjust its internal weights to reduce that loss.
#     - This process repeats for the number of epochs you specify.

import torch
from ultralytics import YOLO
import os

def train_yolo():
    """
    Main function to configure and run the YOLOv8 training process.
    """
    # --- 1. Configuration ---

    # Path to your dataset's YAML file. This file is critical as it tells YOLO
    # the path to your training/validation images and defines the class names.
    data_config_path = os.path.join('robo', 'data.yaml')

    # Choose the base model. 'yolov8n.pt' is the smallest and fastest, perfect for
    # initial tests. For higher accuracy, you can scale up to 'yolov8s.pt',
    # 'yolov8m.pt', etc., but they require more computational power.
    model_variant = 'yolov8n.pt'

    # Training hyperparameters. Feel free to tweak these.
    training_epochs = 100
    image_resolution = 640
    # Batch size depends heavily on your VRAM. Your Intel UHD graphics will likely use
    # shared system RAM, so CPU performance will be the bottleneck. A smaller batch
    # size like 8 or 16 is a safe start. If you were on a dedicated GPU, you could
    # increase this.
    batch_size = 16

    # --- 2. Device Setup ---

    # Let's be smart about hardware. This checks if you have a CUDA-enabled GPU.
    # On your Lenovo Ideapad, this will likely fall back to 'cpu'. If you ever use
    # a machine with an NVIDIA GPU, this script will automatically leverage it.
    device_to_use = 'cuda' if torch.cuda.is_available() else 'cpu'
    print(f"==================================================")
    print(f"🚀 Using device: {device_to_use.upper()}")
    print(f"==================================================")

    # --- 3. Model Loading ---

    # Load the chosen YOLOv8 model. The '.pt' file contains the model architecture
    # and its pre-trained weights.
    print(f"Loading pre-trained model: {model_variant}")
    model = YOLO(model_variant)

    # --- 4. Start Training ---

    print("Training initiated. Let's teach this model something new!")
    print(f"Dataset: {data_config_path}, Epochs: {training_epochs}, Image Size: {image_resolution}x{image_resolution}")

    # This is the magic call. The `.train()` method handles the entire
    # training loop, data loading, augmentation, and saving of results.
    model.train(
        data=data_config_path,
        epochs=training_epochs,
        imgsz=image_resolution,
        batch=batch_size,
        device=device_to_use,
        project='yolov8_training_results', # Directory to save results
        name='run1'                       # Sub-directory for this specific run
    )

    print("\n🎉 Training complete! 🎉")
    print("Your trained model and results are saved in the 'yolov8_training_results' directory.")
    print("The best performing model weights can be found at: yolov8_training_results/run1/weights/best.pt")


if __name__ == '__main__':
    # This is a standard Python construct. It ensures that the `train_yolo()` function
    # is called only when you execute the script directly (e.g., `python train.py`),
    # not when it's imported by another script. It's a good practice for making your
    # code modular and reusable.
    train_yolo()
