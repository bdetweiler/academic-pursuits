; How many days in a month?

(defun days (mon year)
  (case mon 
	((sep apr jun nov) 30)
	((feb) (if (= (mod year 4) 0) 29 28))
	(T 31)))
