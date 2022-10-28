#include "BeatTemp.h"
#include "LabelTemp.h"

namespace vocalshaper {
	BeatTemp::BeatTemp(LabelTemp* labels)
		: labels(labels)
	{
		//添加初始值
		this->list.add({ 0, 0, 4 });
	}

	void BeatTemp::refresh()
	{
		if (!this->labels) {
			return;
		}

		juce::ScopedWriteLock locker1(this->lock);
		juce::ScopedReadLock locker2(this->labels->lock);

		//清空缓存
		this->list.clear();
		this->lastIndex = 0;

		//上一标签状态缓存
		double actPlaceInBeat = 0;			//上一标签生效拍号
		double actPlaceInBar = 0;			//上一标签生效小节

		//已确认有效的标签状态缓存
		double lastInBeat = 0;				//生效拍号
		double lastInBar = 0;				//生效小节
		uint8_t lastBeat = 4;				//设定的节拍

		//添加初始值
		this->list.add({ lastInBeat, lastInBar, lastBeat });

		//计算节拍缓存
		for (int i = 0; i < this->labels->list.size(); i++) {
			auto& currentLabel = this->labels->list.getReference(i);

			//计算标签生效位置
			double labelBeat = std::floor(currentLabel.x);	//标签所在的拍
			double labelBar = lastInBar + std::floor((labelBeat - lastInBeat) / lastBeat);	//标签所在的小节

			//判断标签生效于当前小节还是下一小节
			double labelBarAct = labelBar;
			double labelBeatAct = lastInBeat + (labelBar - lastInBar) * lastBeat;
			if ((uint64_t)(labelBeat - lastInBeat) % lastBeat > 0) {
				labelBarAct++;
				labelBeatAct += lastBeat;
			}

			//根据生效位置判断是否覆盖标签
			if (labelBarAct > actPlaceInBar) {
				//不需覆盖标签
				this->list.add({ labelBeatAct, labelBarAct, currentLabel.beat });
			}
			else {
				//覆盖标签
				auto& last = this->list.getReference(this->list.size() - 1);
				last.beat = currentLabel.beat;
				last.xInBeat = labelBeatAct;
				last.xInBar = labelBarAct;
			}

			if (i < this->labels->list.size() - 1) {
				//非最后标签
				auto& nextLabel = this->labels->list.getReference(i + 1);
				
				//下一标签的位置
				double nextLabelBeat = nextLabel.x;

				//下一标签位置大于当前标签生效位置，意味着当前标签不再被覆盖，标签确实生效，更改生效标签缓存
				if (nextLabelBeat > labelBeatAct) {
					lastInBeat = labelBeatAct;
					lastInBar = labelBarAct;
					lastBeat = currentLabel.beat;
				}
			}
			else {
				//最后标签
				
				//标签确实生效，更改生效标签缓存
				lastInBeat = labelBeatAct;
				lastInBar = labelBarAct;
				lastBeat = currentLabel.beat;
			}

			//记录状态缓存
			actPlaceInBeat = labelBeatAct;
			actPlaceInBar = labelBarAct;
		}
	}

	uint8_t BeatTemp::getBeatAtTime(double x) const
	{
		juce::ScopedReadLock locker1(this->lock);

		//获取块
		auto& current = this->list.getReference(this->selectBy_x(x));

		//返回拍号
		return current.beat;
	}

	double BeatTemp::getBarAtTime(double x) const
	{
		juce::ScopedReadLock locker1(this->lock);

		//获取块
		auto& current = this->list.getReference(this->selectBy_x(x));

		//返回小节号
		return current.xInBar + (x - current.xInBeat) / (double)current.beat;
	}

	double BeatTemp::getTimeAtBar(double bar) const
	{
		juce::ScopedReadLock locker1(this->lock);

		//获取块
		auto& current = this->list.getReference(this->selectBy_bar(bar));

		//返回拍号
		return current.xInBeat + (bar - current.xInBar) * current.beat;
	}

	int BeatTemp::selectBy_x(double x) const
	{
		juce::ScopedReadLock locker1(this->lock);

		//取出缓存的块
		auto& tempBlock = this->list.getReference(this->lastIndex);

		//缓存命中
		if (this->lastIndex == this->list.size() - 1) {
			if (x >= tempBlock.xInBeat) {
				return this->lastIndex;
			}
		}
		else {
			if ((x >= tempBlock.xInBeat) && (x < this->list.getReference(this->lastIndex).xInBeat)) {
				return this->lastIndex;
			}
		}

		//缓存命中下一块
		if (this->lastIndex < this->list.size() - 1) {
			auto& nextBlock = this->list.getReference(this->lastIndex + 1);
			if (this->lastIndex < this->list.size() - 2) {
				if ((x >= nextBlock.xInBeat) && (x < this->list.getReference(this->lastIndex + 2).xInBeat)) {
					return ++(this->lastIndex);
				}
			}
			else {
				if (x >= nextBlock.xInBeat) {
					return ++(this->lastIndex);
				}
			}
		}

		//查找比较函数
		auto CFunc = [](double x, const BeatData& curr, const BeatData& next)->CompareResult {
			if (x >= curr.xInBeat && x < next.xInBeat) {
				return CompareResult::EQ;
			}
			else if (x >= next.xInBeat) {
				return CompareResult::GTR;
			}
			else {
				return CompareResult::LSS;
			}
		};

		//缓存未命中，判断缓存在当前之前还是之后
		if (x < tempBlock.xInBeat) {
			//之前

			//二分查找
			return this->lastIndex = this->search(0, this->lastIndex, x, CFunc);
		}
		else {
			//之后
			
			//如果命中最末
			if (x >= this->list.getReference(this->list.size() - 1).xInBeat) {
				return this->lastIndex = this->list.size() - 1;
			}

			//二分查找
			return this->lastIndex = this->search(this->lastIndex, this->list.size() - 1, x, CFunc);
		}
	}

	int BeatTemp::selectBy_bar(double bar) const
	{
		juce::ScopedReadLock locker1(this->lock);

		//取出缓存的块
		auto& tempBlock = this->list.getReference(this->lastIndex);

		//缓存命中
		if (this->lastIndex == this->list.size() - 1) {
			if (bar >= tempBlock.xInBar) {
				return this->lastIndex;
			}
		}
		else {
			if ((bar >= tempBlock.xInBar) && (bar < this->list.getReference(this->lastIndex).xInBar)) {
				return this->lastIndex;
			}
		}

		//缓存命中下一块
		if (this->lastIndex < this->list.size() - 1) {
			auto& nextBlock = this->list.getReference(this->lastIndex + 1);
			if (this->lastIndex < this->list.size() - 2) {
				if ((bar >= nextBlock.xInBar) && (bar < this->list.getReference(this->lastIndex + 2).xInBar)) {
					return ++(this->lastIndex);
				}
			}
			else {
				if (bar >= nextBlock.xInBar) {
					return ++(this->lastIndex);
				}
			}
		}

		//查找比较函数
		auto CFunc = [](double bar, const BeatData& curr, const BeatData& next)->CompareResult {
			if (bar >= curr.xInBar && bar < next.xInBar) {
				return CompareResult::EQ;
			}
			else if (bar >= next.xInBar) {
				return CompareResult::GTR;
			}
			else {
				return CompareResult::LSS;
			}
		};

		//缓存未命中，判断缓存在当前之前还是之后
		if (bar < tempBlock.xInBar) {
			//之前

			//二分查找
			return this->lastIndex = this->search(0, this->lastIndex, bar, CFunc);
		}
		else {
			//之后

			//如果命中最末
			if (bar >= this->list.getReference(this->list.size() - 1).xInBar) {
				return this->lastIndex = this->list.size() - 1;
			}

			//二分查找
			return this->lastIndex = this->search(this->lastIndex, this->list.size() - 1, bar, CFunc);
		}
	}

	template<typename Func, typename T>
	int BeatTemp::search(int low, int high, T value, Func func) const
	{
		int mid = low + (high - low) / 2;
		if (func(value, this->list.getReference(mid), this->list.getReference(mid + 1)) == CompareResult::EQ) {
			return mid;
		}
		else if (func(value, this->list.getReference(mid), this->list.getReference(mid + 1)) == CompareResult::GTR) {
			return this->search(mid, high, value, func);
		} 
		else {
			return this->search(low, mid, value, func);
		}
	}
}
