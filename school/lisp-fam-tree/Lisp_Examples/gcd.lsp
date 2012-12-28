; Find the greatest common divisor...
; Here's an example (that you might be able to find somewhere).
;
; Bill Mahoney

(defun mygcd(x y)
  (cond ((= 0 y) x)
	(t (mygcd y (mod x y)))
	))

(print (mygcd 100 4))

