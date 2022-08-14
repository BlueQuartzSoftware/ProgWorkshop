from typing import List, Tuple, Union
from dream3d.Filter import Filter, FilterDelegatePy
# Import some basic SIMPL C++ objects that are required
from dream3d.simpl import DataContainerArray, FilterDelegateCpp, FilterParameter, DataArrayPath
# Import the needed Filter Parameters
from dream3d.simpl import DataArraySelectionFilterParameter, DataArrayCreationFilterParameter
from dream3d.simpl import IntFilterParameter, FloatFilterParameter
from dream3d.simpl import InputPathFilterParameter, InputFileFilterParameter
from dream3d.simpl import BooleanFilterParameter, StringFilterParameter, ChoiceFilterParameter
from dream3d.simpl import NumericTypes


class ExampleFilter(Filter):
  def __init__(self) -> None:
    self.int_param: int = 5
    self.dap_param: DataArrayPath = DataArrayPath('', '', '')
    self.str_param: str = "Something"
    self.bool_param:bool = False
    self.input_file_param:str = "/No/Path/anywhere.txt"
    self.input_path_param:str = "/Some/Folder/Somewhere"
    self.float_param:float = 33.44
    self.axes: int = 0
    self.created_data_array_path: DataArrayPath = DataArrayPath('', '', '')

  def _set_axes(self, value: int) -> None:
      self.axes = value

  def _get_axes(self) -> int:
      return self.axes

  def _set_created_data_array_path(self, value: DataArrayPath) -> None:
      self.created_data_array_path = value

  def _get_created_data_array_path(self) -> DataArrayPath:
      return self.created_data_array_path

  def _set_float_param(self, value: float) -> None:
      self.float_param = value
  def _get_float_param(self) -> float:
      return self.float_param

  def _set_int(self, value: int) -> None:
    self.int_param = value

  def _get_int(self) -> int:
    return self.int_param

  def _set_dap(self, value: DataArrayPath) -> None:
    self.dap_param = value

  def _get_dap(self) -> DataArrayPath:
    return self.dap_param

  def _get_str(self) -> str:
      return self.str_param

  def _set_str(self, value: str) -> None:
      self.str_param = value

  def _get_bool(self) -> bool:
      return self.bool_param

  def _set_bool(self, value ) -> None:
      self.bool_param = value

  def _get_input_file(self) -> str:
      return self.input_file_param

  def _set_input_file(self, value: str ) -> None:
      self.input_file_param = value
  
  def _get_input_path_param(self) -> str:
      return self.input_path_param  

  def _set_input_path_param(self, value: str) -> None:
      self.input_path_param = value

  

  @staticmethod
  def name() -> str:
    return 'ExampleFilter'

  @staticmethod
  def uuid() -> str:
    return '{2f2a6f35-d488-59d7-bd8b-8a234e5700b3}'

  @staticmethod
  def group_name() -> str:
    return 'Example'

  @staticmethod
  def sub_group_name() -> str:
    return 'Sub Example'

  @staticmethod
  def human_label() -> str:
    return 'Example Filter [Python]'

  @staticmethod
  def version() -> str:
    return '1.0.0'

  @staticmethod
  def compiled_lib_name() -> str:
    return 'Python'

  def setup_parameters(self) -> List[FilterParameter]:
    req = DataArraySelectionFilterParameter.RequirementType()
    return [
        IntFilterParameter('Integer', 'int_param', self.int_param, FilterParameter.Category.Parameter, self._set_int, self._get_int, -1),
        DataArraySelectionFilterParameter('Data Array Path Selection', 'dap_param', self.dap_param, FilterParameter.Category.RequiredArray, self._set_dap, self._get_dap, req, -1),
        StringFilterParameter('String', 'str_param', self.str_param, FilterParameter.Category.Parameter, self._set_str, self._get_str, -1),
        BooleanFilterParameter('Boolean', 'bool_param', self.bool_param, FilterParameter.Category.Parameter, self._set_bool, self._get_bool, -1),
        InputFileFilterParameter('Input File', 'input_file_param', self.input_file_param, 
                                    FilterParameter.Category.Parameter, self._set_input_file, self._get_input_file,'*.ang', 'EDAX Ang', -1),
        InputPathFilterParameter('Input Directory', 'input_path_param', self.input_path_param, 
                                    FilterParameter.Category.Parameter, self._set_input_path_param, self._get_input_path_param, -1),
        ChoiceFilterParameter('Slice Axis', 'axes', self.axes, FilterParameter.Category.Parameter, self._set_axes,
                                  self._get_axes, ["x", "y", "z"], False, -1),
        DataArrayCreationFilterParameter('New Array', 'new_array', self.created_data_array_path,
                                             FilterParameter.Category.CreatedArray, self._set_created_data_array_path,
                                             self._get_created_data_array_path,
                                             DataArrayCreationFilterParameter.RequirementType(), -1)
    ]

  def data_check(self, dca: DataContainerArray, delegate: Union[FilterDelegateCpp, FilterDelegatePy] = FilterDelegatePy()) -> Tuple[int, str]:
    am = dca.getAttributeMatrix(self.path)

    if am is None:
      return (-1, 'AttributeMatrix is None')

    da = am.getAttributeArray(self.path)
    if da is None:
      return (-2, 'DataArray is None')

    delegate.notifyStatusMessage('data_check finished!')

    return (0, 'Success')

  def _execute_impl(self, dca: DataContainerArray, delegate: Union[FilterDelegateCpp, FilterDelegatePy] = FilterDelegatePy()) -> Tuple[int, str]:
    delegate.notifyStatusMessage(f'foo = {self.foo}')

    da = dca.getAttributeMatrix(self.path).getAttributeArray(self.path)

    data = da.npview()
    delegate.notifyStatusMessage(f'before = {data}')
    data += self.foo
    delegate.notifyStatusMessage(f'after = {data}')

    delegate.notifyStatusMessage('execute finished!')
    return (0, 'Success')

filters = [ExampleFilter]
