from torchvision import models
import torch
from torchvision.models import mobilenet_v3_small
from torchvision.models.mobilenetv3 import MobileNet_V3_Small_Weights
from torchvision import transforms
from PIL import Image
# import matplotlib.pyplot as plt


model = mobilenet_v3_small(weights=MobileNet_V3_Small_Weights.DEFAULT)

# dir(models)

mobilenet_v3_small = models.mobilenet_v3_small(weights=MobileNet_V3_Small_Weights.DEFAULT)
# print(mobilenetv2)


transform = transforms.Compose([
    transforms.Resize(256),
    transforms.CenterCrop(224),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406],
                          std=[0.229, 0.224, 0.225]),
])

img = Image.open("capture_0000.jpg")
img = img.rotate(90)




img_t = transform(img)

batch_t = torch.unsqueeze(img_t, 0)
mobilenet_v3_small.eval()
out = mobilenet_v3_small(batch_t)
# print(out.shape)
with open('trash_classes.txt') as f:
    labels = [line.strip() for line in f.readlines()]
_, index = torch.max(out, 1)
percentage = torch.nn.functional.softmax(out, dim=1)[0]*100
print(labels[index[0]], percentage[index[0]].item())
# _, indices = torch.sort(out, descending=True)
# [(labels[idx], percentage[idx].item()) for idx in indices[0][:4]]
