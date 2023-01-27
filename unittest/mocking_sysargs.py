from datetime import datetime
import sys
from unittest.mock import patch

with patch("sys.argv", ["--action", "--run-test"]):
  print(sys.argv)
