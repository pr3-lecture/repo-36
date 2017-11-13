require File.expand_path(File.dirname(__FILE__) + '/neo')

class AboutHashes < Neo::Koan
  def test_creating_hashes
    empty_hash = Hash.new
    assert_equal Hash, empty_hash.class
    assert_equal({}, empty_hash)
    assert_equal 0, empty_hash.size
  end

  # You can create hashes using {}

  def test_hash_literals
    hash = { :one => "uno", :two => "dos" }
    assert_equal 2, hash.size
  end

  def test_accessing_hashes
    hash = { :one => "uno", :two => "dos" }
    assert_equal "uno", hash[:one]
    assert_equal "dos", hash[:two]
    assert_equal nil, hash[:doesnt_exist]
  end

  def test_accessing_hashes_with_fetch
    hash = { :one => "uno" }
    assert_equal "uno", hash.fetch(:one)
    assert_raise(KeyError) do
      hash.fetch(:doesnt_exist)
    end

    # THINK ABOUT IT:
    #
    # Why might you want to use #fetch instead of #[] when accessing hash keys?

    # https://stackoverflow.com/questions/16569409/fetch-vs-when-working-with-hashes
    #     By default, using #[] will retrieve the hash value if it exists, and return nil if it doesn't exist *.
    #
    #     Using #fetch gives you a few options (see the docs on #fetch):
    #
    #     fetch(key_name): get the value if the key exists, raise a KeyError if it doesn't
    #     fetch(key_name, default_value): get the value if the key exists, return default_value otherwise
    #     fetch(key_name) { |key| "default" }: get the value if the key exists, otherwise run the supplied block and return the value.
    #
    #     Each one should be used as the situation requires, but #fetch is very feature-rich and can handle many cases depending on how it's used.
    #     For that reason I tend to prefer it over accessing keys with #[].

  end

  def test_changing_hashes
    hash = { :one => "uno", :two => "dos" }
    hash[:one] = "eins"

    expected = { :one => "eins", :two => "dos" }
    assert_equal expected, hash

    # Bonus Question: Why was "expected" broken out into a variable
    # rather than used as a literal?
  end

  def test_hash_is_unordered
    hash1 = { :one => "uno", :two => "dos" }
    hash2 = { :two => "dos", :one => "uno" }

    assert_equal true, hash1 == hash2
  end

  # Den Inhalt zweier Objekte vergleicht man in Ruby mit "==".

  def test_hash_keys
    hash = { :one => "uno", :two => "dos" }
    assert_equal 2, hash.keys.size
    assert_equal true, hash.keys.include?(:one)
    assert_equal true, hash.keys.include?(:two)
    assert_equal Array, hash.keys.class
  end
  # include?(key)"Returns true if the given key is present in hsh."
  # hash.keys returns an array with the keys.

  def test_hash_values
    hash = { :one => "uno", :two => "dos" }
    assert_equal 2, hash.values.size
    assert_equal true, hash.values.include?("uno")
    assert_equal true, hash.values.include?("dos")
    assert_equal Array, hash.values.class
  end

  # "values" returns the values from the hash.
  # include?(value) returns true if the given value is present in hash.

  def test_combining_hashes
    hash = { "jim" => 53, "amy" => 20, "dan" => 23 }
    new_hash = hash.merge({ "jim" => 54, "jenny" => 26 })

    assert_equal true, hash != new_hash

    expected = { "jim" => 54, "amy" => 20, "dan" => 23, "jenny" => 26 }
    assert_equal true, expected == new_hash
  end

      # merge(other_hash)
      # merge(other_hash){|key, oldval, newval| block}
      #
      # Returns a new hash containing the contents of other_hash and the contents of hsh.
      # If no block is specified, the value for entries with duplicate keys will be that of other_hash. Otherwise
      # the value for each duplicate key is determined by calling the block with the key, its value in hsh and its value in other_hash.

  def test_default_value
    hash1 = Hash.new
    hash1[:one] = 1

    assert_equal 1, hash1[:one]
    assert_equal nil, hash1[:two]

    hash2 = Hash.new("dos")
    # hash2 -> {}
    # hash2.keys -> {}
    hash2[:one] = 1
    # hash2.keys -> [:one]

    assert_equal 1, hash2[:one]
    assert_equal "dos", hash2[:two]
    # instead of returning nil it returns the default object.
  end

    # new -> new_hash
    # new.(obj) -> new_hash
    # Returns a new, empty hash. If this hash is subsequently accessed by a key that doesn't correspond to a hash entry,
    # the value returned depends on the style of new used to create the hash.
    # In the first form, the access returns nil. If obj is specified, this single object will be used for all default values.
    # The default object in this example is "dos". hash2.keys -> [:one]


  def test_default_value_is_the_same_object
    hash = Hash.new([])

    hash[:one] << "uno"
    hash[:two] << "dos"
    # hash[:four] -> ["uno","dos"]
    # hash.keys -> []
    # hash[:four] = 1
    # hash.keys -> [:four]

    assert_equal ["uno","dos"], hash[:one]
    assert_equal ["uno","dos"], hash[:two]
    assert_equal ["uno","dos"], hash[:three]

    assert_equal true, hash[:one].object_id == hash[:two].object_id
  end

     #  ary << obj → ary
     # Append—Pushes the given object on to the end of this array.
     # This expression returns the array itself, so several appends may be chained together.
     # hash = Hash.new("dos")
     # hash[:one]
     # => "dos" default object
     # hash[:one] << "uno"
     # hash[:one] << "dosuno"
     # if the value is 1 (integer) then 1 << 2 -> 4. The binary representation of 1 gets shifted to the left 2 times (0001 -> 0100)

  def test_default_value_with_block
    hash = Hash.new {|hash, key| hash[key] = [] }

    hash[:one] << "uno"
    hash[:two] << "dos"
    assert_equal [:one,:two], hash.keys
    assert_equal ["uno"], hash[:one]
    assert_equal ["dos"], hash[:two]
    assert_equal [], hash[:three]
  end

  # If a block is specified, it will be called with the hash object and the key,
  # and should return the default value. It is the block's responsibility to store the value in the hash if required.
end
