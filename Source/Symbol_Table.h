// This is source code is put inside the header because I keep getting an
// unkonwn symbol error.

#pragma once

#include <concepts>
#include <stdexcept>
#include <memory>

namespace Klang {

template<std::equality_comparable Key_T, typename Value_T>
class Symbol_Table {
public:
	using This_Type = Symbol_Table;
	using Key_Type = Key_T;
	using Value_Type = Value_T;

public:
	class Symbol {
		friend class Symbol_Table<Key_T, Value_T>;
	
	public:
		using This_Type = Symbol;
		using Key_Type = Key_T;
		using Value_Type = Value_T;
		using Bias_Type = unsigned char;
	
	public:
		Symbol() = delete;
		Symbol(This_Type&&) = delete;
		Symbol(This_Type const&) = delete;
		
		Symbol& operator=(This_Type&&) = delete;
		Symbol& operator=(This_Type const&) = delete;
		
		constexpr Symbol(Key_Type const& key, Value_Type const& value,
				 This_Type* parent = nullptr, Bias_Type bias = 0) noexcept
			: key_(key), value_(value), bias_(bias), parent_(parent) {}

		~Symbol() {
			this->detach();
			while (this->child() != nullptr)
				delete this->child_;
		}
	
	public:
		constexpr Key_Type const& key() const noexcept { return this->key_; }
		
		constexpr Value_Type& value() noexcept { return this->value_; }
		constexpr Value_Type const& value() const noexcept { return this->value_; }
	
		constexpr Bias_Type bias() const noexcept { return this->bias_; }
		
		constexpr This_Type* parent() noexcept { return this->parent_; }
		constexpr This_Type const* parent() const noexcept { return this->parent_; }
		constexpr This_Type const* child() const noexcept { return this->child_; }
		
		constexpr This_Type const* prior() const noexcept { return this->prior_; }
		constexpr This_Type const* next() const noexcept { return this->next_; }
	
	public:
		void nullify_biases() noexcept {
			for (This_Type* curr = this->child_; curr; curr = curr->next_)
				curr->bias_ = 0;
		}
	
	private:
		Key_Type key_;
		Value_Type value_;
		Bias_Type bias_;
		This_Type* parent_ = nullptr;
		This_Type* child_ = nullptr;
		This_Type* prior_ = nullptr;
		This_Type* next_ = nullptr;
	
	private:
		void detach() noexcept {
			if (this->prior())
				this->prior_->next_ = this->next_;
			else if (this->parent())
				this->parent_->child_ = this->next_;
			if (this->next())
				this->next_->prior_ = this->prior_;
		}
		
		void prepend(This_Type& other) noexcept {
			other.prior_ = this->prior_;
			other.next_ = this;
			if (this->prior())
				this->prior_->next_ = &other;
			else this->parent_->child_ = &other;
			this->prior_ = &other;
		}
		
		void append(This_Type& other) noexcept {
			other.prior_ = this;
			other.next_ = this->next_;
			if (this->next())
				this->next_->prior_ = &other;
			this->next_ = &other;
		}
	
		void increase_bias() noexcept {
			++this->bias_;
			This_Type* curr = this->prior_;
			if (!curr)
				return;
			this->detach();
			for (;; curr = curr->prior_) {
				if (curr->bias() > this->bias()) {
					curr->append(*this);
					return;
				}
				if (!curr->prior()) {
					curr->prepend(*this);
					return;
				}
			}
		}
	};

public:
	using Symbol_Type = Symbol;
	// TODO: Figure out a better name for this:
	using Append_If_Type = bool (*)(Symbol_Type const& entry, Symbol_Type const& child);

public:
	Symbol_Table() = default;
	Symbol_Table(Symbol&&) = delete;
	Symbol_Table(Symbol const&) = delete;

	Symbol_Table& operator=(Symbol_Table&&) = delete;
	Symbol_Table& operator=(Symbol_Table const&) = delete;
	
	~Symbol_Table() noexcept {
		delete this->root_;
	}

public:
	constexpr Symbol* root() noexcept { return this->root_; }
	constexpr Symbol const* root() const noexcept { return this->root_; }

public:
	static constexpr Append_If_Type default_append_if =
		[](Symbol_Type const& entry, Symbol_Type const& child) noexcept {
		return child.bias() > entry.bias();
	};

	void enter(Symbol& entry, Append_If_Type append_if = This_Type::default_append_if) {
		if (!entry.parent()) {
			this->root_ = &entry;
			return;
		}
		Symbol* child = entry.parent_->child_;
		if (!child) {
			entry.parent_->child_ = &entry;
			return;
		}
		for (;; child = child->next_) {
			if (child->key() == entry.key())
				throw std::invalid_argument(__FUNCTION__);
			if (!child->next())
				break;
		}
		for (;; child = child->prior_) {
			if (append_if(*child, entry)) {
				child->append(entry);
				return;
			}
			if (!child->prior())
				break;
		}
		child->prepend(entry);
	}

	// If `parent` is `nullptr`, access an entry in `this->root_`; otherwise,
	// access an entry in `parent->child_`.
	Value_Type& access(Key_Type const& key, Symbol* parent = nullptr) {
		Symbol* curr = (parent != nullptr)
			? parent->child_ : this->root_;
		for (; curr; curr = curr->next_) {
			if (curr->key() == key)
				return curr->value();
		}
		throw std::invalid_argument(__FUNCTION__);
	}

private:
	Symbol* root_ = nullptr;
};

template<std::equality_comparable Key_T, typename Value_T>
using Symbol = typename Symbol_Table<Key_T, Value_T>::Symbol;

}
