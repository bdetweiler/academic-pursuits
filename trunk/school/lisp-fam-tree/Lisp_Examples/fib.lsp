; Fibonacci number calculator example
; Bill Mahoney
;
; You give me N, and I give you number pair N

(defun fib (N)
  (let ((temp)) ; temporary variable, uninitialized
    (cond ((< N 1)
	   (format t "Invalid input number: " )
	   (print N) nil)
	  ((= N 1)
	   (list 1 1))
	  (T
	   (setq temp (fib (- n 1))) ; Calculate N-1
	   (print temp)
	   (list (cadr temp) (+ (car temp) (cadr temp))))
	  )))

; See if we can calculate the golden ratio from a large Fibonacci number.
; Golden ratio is +/- 0.6180339887... and +/- 1.6180339887, the latter is the
; one that is more commonly seen.
(defun golden (N)
  (let* ((pair (fib N))
	 (myfirst (car pair))
	 (second (cadr pair)))
    (print myfirst) (print second)
    (/ (float second) (float myfirst))))

