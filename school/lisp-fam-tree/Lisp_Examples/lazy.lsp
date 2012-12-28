;
; This will demo that lisp does lazy evaluation of parameters and not eager 
; evaluation of parameters. So there.
;
; Bill Mahoney
; For CSCI 4220
;

(defun func (p1 p2 p3)
  (cond ((= p1 p2) (+ p1 p2)) ; If the first two are equal, add them
	((< p1 p2) (- p2 p1)) ; If the first is less, subtract it from second
	(T (+ p3 1))))        ; Otherwise EVALUATE and return p3
                              ; But it had better be a number!
