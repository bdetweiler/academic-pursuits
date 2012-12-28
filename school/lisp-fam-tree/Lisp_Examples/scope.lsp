; Let's prove to ourselves that the variable scope is dynamic.  To do
; so, we'll set a global called "the-local" to some name, then call
; the function. You'll see that it creates a local with this name.
; We'll do this to a global (instead of a "let" so that after the fact
; we can prove that it really worked.

(defun show-scope ()
  (setq temp the-local) ; Evaluates "the-local" and sets "temp" to this name.
  (set temp 'it-worked) ; Sets the variable named whatever to "it-worked"
       (format t "A new variable named ") (prin1 temp) (format t " has been assigned.~%")
       )


; Demo this...
(setq the-local 'variable)
(show-scope)

; At this point, the variable named "variable" has been assigned to!
(format t "the-local=~s~%" the-local)
(format t "variable=~s~%" variable)
