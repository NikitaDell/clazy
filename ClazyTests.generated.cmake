# This file was autogenerated by running: ./dev-scripts/generate.py --generate

macro(add_clazy_test name)
  add_test(NAME ${name} COMMAND python3 run_tests.py ${name} --verbose WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/)
  set_property(TEST ${name} PROPERTY
    ENVIRONMENT "CLAZYPLUGIN_CXX=$<TARGET_FILE:ClazyPlugin>;CLAZYSTANDALONE_CXX=$<TARGET_FILE:clazy-standalone>;$<$<BOOL:${HAS_STD_FILESYSTEM}>:CLAZY_HAS_FILESYSTEM=>"
  )
endmacro()

add_clazy_test(assert-with-side-effects)
add_clazy_test(container-inside-loop)
add_clazy_test(detaching-member)
add_clazy_test(heap-allocated-small-trivial-type)
add_clazy_test(ifndef-define-typo)
add_clazy_test(isempty-vs-count)
add_clazy_test(jni-signatures)
add_clazy_test(qhash-with-char-pointer-key)
add_clazy_test(qproperty-type-mismatch)
add_clazy_test(qrequiredresult-candidates)
add_clazy_test(qstring-varargs)
add_clazy_test(qt-keyword-emit)
add_clazy_test(qt-keywords)
add_clazy_test(qt4-qstring-from-array)
add_clazy_test(qt6-deprecated-api-fixes)
add_clazy_test(qt6-fwd-fixes)
add_clazy_test(qt6-header-fixes)
add_clazy_test(qt6-qhash-signature)
add_clazy_test(qt6-qlatin1stringchar-to-u)
add_clazy_test(qvariant-template-instantiation)
add_clazy_test(raw-environment-function)
add_clazy_test(reserve-candidates)
add_clazy_test(sanitize-inline-keyword)
add_clazy_test(signal-with-return-value)
add_clazy_test(thread-with-slots)
add_clazy_test(tr-non-literal)
add_clazy_test(unexpected-flag-enumerator-value)
add_clazy_test(unneeded-cast)
add_clazy_test(unused-result-check)
add_clazy_test(use-arrow-operator-instead-of-data)
add_clazy_test(use-chrono-in-qtimer)
add_clazy_test(connect-by-name)
add_clazy_test(connect-non-signal)
add_clazy_test(connect-not-normalized)
add_clazy_test(container-anti-pattern)
add_clazy_test(empty-qstringliteral)
add_clazy_test(fully-qualified-moc-types)
add_clazy_test(lambda-in-connect)
add_clazy_test(lambda-unique-connection)
add_clazy_test(lowercase-qml-type-name)
add_clazy_test(mutable-container-key)
add_clazy_test(no-module-include)
add_clazy_test(overloaded-signal)
add_clazy_test(qcolor-from-literal)
add_clazy_test(qdatetime-utc)
add_clazy_test(qenums)
add_clazy_test(qfileinfo-exists)
add_clazy_test(qgetenv)
add_clazy_test(qmap-with-pointer-key)
add_clazy_test(qstring-arg)
add_clazy_test(qstring-comparison-to-implicit-char)
add_clazy_test(qstring-insensitive-allocation)
add_clazy_test(qstring-ref)
add_clazy_test(qt-macros)
add_clazy_test(strict-iterators)
add_clazy_test(temporary-iterator)
add_clazy_test(unused-non-trivial-variable)
add_clazy_test(use-static-qregularexpression)
add_clazy_test(writing-to-temporary)
add_clazy_test(wrong-qevent-cast)
add_clazy_test(wrong-qglobalstatic)
add_clazy_test(auto-unexpected-qstringbuilder)
add_clazy_test(child-event-qobject-cast)
add_clazy_test(connect-3arg-lambda)
add_clazy_test(const-signal-or-slot)
add_clazy_test(detaching-temporary)
add_clazy_test(foreach)
add_clazy_test(incorrect-emit)
add_clazy_test(install-event-filter)
add_clazy_test(non-pod-global-static)
add_clazy_test(overridden-signal)
add_clazy_test(post-event)
add_clazy_test(qdeleteall)
add_clazy_test(qhash-namespace)
add_clazy_test(qlatin1string-non-ascii)
add_clazy_test(qproperty-without-notify)
add_clazy_test(qstring-left)
add_clazy_test(range-loop-detach)
add_clazy_test(range-loop-reference)
add_clazy_test(returning-data-from-temporary)
add_clazy_test(rule-of-two-soft)
add_clazy_test(skipped-base-method)
add_clazy_test(virtual-signal)
add_clazy_test(base-class-event)
add_clazy_test(copyable-polymorphic)
add_clazy_test(ctor-missing-parent-argument)
add_clazy_test(function-args-by-ref)
add_clazy_test(function-args-by-value)
add_clazy_test(global-const-char-pointer)
add_clazy_test(implicit-casts)
add_clazy_test(missing-qobject-macro)
add_clazy_test(missing-typeinfo)
add_clazy_test(old-style-connect)
add_clazy_test(qstring-allocations)
add_clazy_test(returning-void-expression)
add_clazy_test(rule-of-three)
add_clazy_test(static-pmf)
add_clazy_test(virtual-call-ctor)