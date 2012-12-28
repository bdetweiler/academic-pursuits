; File: Hello-World.lsp

(defun Hello-World ()
    (princ "\nHello Lisp World\n\n")
    (dotimes (i 5) (princ "        ") (print i))
)

