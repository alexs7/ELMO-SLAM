import numpy as np
from sklearn.metrics import jaccard_score

y_true = # the current class gt labels
y_pred = # the current class prediction labels

print(jaccard_score(y_true[0], y_pred[0])) # will return a score 0-1, we can use a percentage here ?
