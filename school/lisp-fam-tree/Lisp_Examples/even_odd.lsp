(defun pred (X)
  (- x 1))

(defun even (X)
  (cond ( (= 0 X) T )
	( (= 1 X) nil )
	( (odd (pred X)) T )))

(defun odd (X)
  (cond ( (= 0 X) nil )
	( (= 1 X) T )
	( (even (pred X)) T )))

