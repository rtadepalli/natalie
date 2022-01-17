class Integer
  class << self
    def try_convert(n)
      if n.is_a?(Integer)
        n
      elsif n.respond_to?(:to_int)
        n.to_int.tap do |result|
          if result && !result.is_a?(Integer)
            raise TypeError, "can't convert #{n.class} to Integer (#{n.class}#to_int gives #{result.class})"
          end
        end
      else
        nil
      end
    end

  end

  def div(n)
    if !n.is_a?(Numeric) && n.respond_to?(:coerce)
      a, b = n.coerce(self)
      a.div(b)
    else
      super
    end
  end

  def downto(n)
    return enum_for(:downto, n) { self >= n ? (self - n + 1) : 0 } unless block_given?

    i = self
    until i < n
      yield i
      i -= 1
    end
  end

  def upto(n)
    return enum_for(:upto, n) { self <= n ? (n - self + 1) : 0 } unless block_given?

    i = self
    until i > n
      yield i
      i += 1
    end
  end

  def allbits?(mask)
    raise TypeError, "No implicit conversion of #{mask.class} into Integer" unless mask.respond_to?(:to_int)

    int_mask = mask.to_int

    unless int_mask.is_a?(Integer)
      raise TypeError, "can't convert #{mask.class} to Integer (#{mask.class}#to_int gives #{int_mask.class})"
    end

    (self & int_mask) == int_mask
  end

  def anybits?(mask)
    raise TypeError, "No implicit conversion of #{mask.class} into Integer" unless mask.respond_to?(:to_int)

    int_mask = mask.to_int

    unless int_mask.is_a?(Integer)
      raise TypeError, "can't convert #{mask.class} to Integer (#{mask.class}#to_int gives #{int_mask.class})"
    end

    (self & int_mask) != 0
  end

  def nobits?(mask)
    raise TypeError, "No implicit conversion of #{mask.class} into Integer" unless mask.respond_to?(:to_int)

    int_mask = mask.to_int

    unless int_mask.is_a?(Integer)
      raise TypeError, "can't convert #{mask.class} to Integer (#{mask.class}#to_int gives #{int_mask.class})"
    end

    (self & int_mask) == 0
  end

  def integer?
    true
  end
end
